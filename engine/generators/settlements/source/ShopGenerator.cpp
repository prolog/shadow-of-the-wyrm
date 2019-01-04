#include "ShopGenerator.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapItemGenerator.hpp"
#include "Naming.hpp"
#include "RNG.hpp"
#include "Shop.hpp"

using namespace std;

bool ShopGenerator::generate_shop(MapPtr map, const Building& building)
{
  bool shop_created = false;

  if (map != nullptr)
  {
    Game& game = Game::instance();

    // Create a shop by determining the item types, setting up the shop
    // details, creating a shopkeeper, and naming it.
    vector<ItemType> stocked_types = get_random_item_types();
    string shopkeeper_name = Naming::generate_name(static_cast<CreatureSex>(RNG::range(0, 1)));

    CreatureFactory cf;
    CreaturePtr shopkeeper = cf.create_by_creature_id(game.get_action_manager_ref(), CreatureID::CREATURE_ID_SHOPKEEPER, map);
    
    if (shopkeeper != nullptr)
    {
      shopkeeper->set_name(shopkeeper_name);

      pair<Coordinate, Coordinate> interior_coords = building.get_interior_coords();
      vector<Coordinate> ic = CoordUtils::get_coordinates_in_range(interior_coords.first, interior_coords.second);

      // Setup the shop details.  Create the shop in the map, and then repop
      // it to seed the initial items.
      if (!ic.empty())
      {
        std::shuffle(ic.begin(), ic.end(), RNG::get_engine());
        Coordinate shopkeeper_coords = ic.at(RNG::range(0, ic.size()-1));

        GameUtils::add_new_creature_to_map(game, shopkeeper, map, shopkeeper_coords);
        Shop shop;
        string shop_id = shopkeeper_name + "_shop";

        shop.set_start(interior_coords.first);
        shop.set_end(interior_coords.second);
        shop.set_shopkeeper_id(shopkeeper->get_id());
        shop.set_stocked_item_types(stocked_types);
        shop.set_shop_id(shop_id);
        
        map->get_shops_ref().insert(make_pair(shop_id, shop));

        // Set a temporary danger level.  The danger level is typically not
        // initialized until after the map has been generated, so creating
        // a shop without doing this will result in an empty shop, because
        // the danger level is 0.  Revert after so that the code calling the
        // generator can set a danger level appropriately.
        int old_danger_level = map->get_danger();
        map->set_danger(RNG::range(2, 50));

        MapItemGenerator mig;
        mig.repop_shop(map, shop_id);

        map->set_danger(old_danger_level);

        shop_created = true;
      }
    }
  }

  return shop_created;
}

vector<ItemType> ShopGenerator::get_random_item_types()
{
  int val = RNG::range(1, 100);

  if (val < 20)
  {
    return get_magical_item_types();
  }
  else if (val < 35)
  {
    return get_jewelry_item_types();
  }
  else if (val < 80)
  {
    return get_weapons_and_armour_types();
  }
  else
  {
    return get_misc_item_types();
  }
}

vector<ItemType> ShopGenerator::get_magical_item_types()
{
  return {ItemType::ITEM_TYPE_POTION, ItemType::ITEM_TYPE_WAND, ItemType::ITEM_TYPE_SCROLL, ItemType::ITEM_TYPE_SPELLBOOK, ItemType::ITEM_TYPE_FOOD};
}

vector<ItemType> ShopGenerator::get_jewelry_item_types()
{
  return {ItemType::ITEM_TYPE_AMULET, ItemType::ITEM_TYPE_RING, ItemType::ITEM_TYPE_FOOD};
}

vector<ItemType> ShopGenerator::get_weapons_and_armour_types()
{
  return {ItemType::ITEM_TYPE_AMMUNITION, ItemType::ITEM_TYPE_ARMOUR, ItemType::ITEM_TYPE_WEAPON, ItemType::ITEM_TYPE_FOOD};
}

vector<ItemType> ShopGenerator::get_misc_item_types()
{
  return {ItemType::ITEM_TYPE_FOOD, ItemType::ITEM_TYPE_PLANT, ItemType::ITEM_TYPE_BOAT, ItemType::ITEM_TYPE_TOOL};
}

