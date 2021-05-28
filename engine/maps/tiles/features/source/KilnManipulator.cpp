#include "KilnManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "KilnScreen.hpp"
#include "ItemTypes.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

KilnManipulator::KilnManipulator(FeaturePtr feature)
: FeatureManipulator(feature),
  crafting_functions({ {0, &KilnManipulator::create_clay_pot},
                       {1, &KilnManipulator::create_clay_shot},
                       {2, &KilnManipulator::create_fire_bomb},
                       {3, &KilnManipulator::create_shadow_bomb} })
{
}

void KilnManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_KILN));
    manager.send();
  }
}

bool KilnManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool kiln_used = false;

  if (feature != nullptr && creature != nullptr)
  {
    if (check_for_clay(creature))
    {
      Game& game = Game::instance();
      DisplayPtr display = game.get_display();

      bool fire_bombs = creature->get_inventory()->has_item(ItemIdKeys::ITEM_ID_MAGICI_SHARD);
      bool shadow_bombs = creature->get_inventory()->has_item(ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE);

      KilnScreen ks(display, fire_bombs, ItemIdKeys::ITEM_ID_MAGICI_SHARD, shadow_bombs, ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE);
      string d = ks.display();

      // Call the appropriate function based on the response:
      if (!d.empty())
      {
        int idx = tolower(d.at(0)) - 'a';
        auto f_it = crafting_functions.find(idx);

        if (f_it != crafting_functions.end())
        {
          auto f_p = f_it->second;
          kiln_used = (this->*f_p)(creature);
        }
      }
    }
  }

  return kiln_used;
}

bool KilnManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}

bool KilnManipulator::check_for_clay(CreaturePtr creature)
{
  bool has_clay = false;

  if (creature != nullptr)
  {
    if (creature->get_inventory()->count_items(ItemIdKeys::ITEM_ID_CLAY) == 0)
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KILN_NO_CLAY));
      manager.send();
    }
    else
    {
      has_clay = true;
    }
  }

  return has_clay;
}

ItemPtr get_item(const string& item_base_id, CreaturePtr creature)
{
  ItemPtr item;

  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();

  list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_base_id_filter(item_base_id);
  item = am.inventory(creature, creature->get_inventory(), display_filter_list, {}, false, false);

  return item;
}

bool KilnManipulator::create_clay_item(const vector<string>& component_item_ids, const string& crafted_item_id, const int rng_min, const int rng_max, CreaturePtr creature)
{
  // ...
  return false;
}

bool KilnManipulator::create_clay_pot(CreaturePtr creature)
{
  return create_clay_item({ ItemIdKeys::ITEM_ID_CLAY }, ItemIdKeys::ITEM_ID_CLAY_POT, 1, 1, creature);
}

bool KilnManipulator::create_clay_shot(CreaturePtr creature)
{
  return create_clay_item({ ItemIdKeys::ITEM_ID_CLAY }, ItemIdKeys::ITEM_ID_CLAY_SHOT, 12, 30, creature);
}

bool KilnManipulator::create_fire_bomb(CreaturePtr creature)
{
  return create_clay_item({ ItemIdKeys::ITEM_ID_CLAY, ItemIdKeys::ITEM_ID_MAGICI_SHARD }, ItemIdKeys::ITEM_ID_FIRE_BOMB, 3, 4, creature);
}

bool KilnManipulator::create_shadow_bomb(CreaturePtr creature)
{
  return create_clay_item({ ItemIdKeys::ITEM_ID_CLAY, ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE }, ItemIdKeys::ITEM_ID_SHADOW_BOMB, 3, 4, creature);
}
