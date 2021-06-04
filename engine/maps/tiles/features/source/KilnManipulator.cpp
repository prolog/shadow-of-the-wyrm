#include "KilnManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "KilnCalculator.hpp"
#include "KilnScreen.hpp"
#include "ItemTypes.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

KilnManipulator::KilnManipulator(FeaturePtr feature)
: FeatureManipulator(feature),
  crafting_functions({ {0, {&KilnManipulator::create_clay_pot, &KilnManipulator::verify_clay_pot}},
                       {1, {&KilnManipulator::create_clay_shot, &KilnManipulator::verify_clay_shot}},
                       {2, {&KilnManipulator::create_fire_bomb, &KilnManipulator::verify_fire_bomb}},
                       {3, {&KilnManipulator::create_shadow_bomb, &KilnManipulator::verify_shadow_bomb}} })
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
        if (d.at(0) == '-')
        {
          return notify_on_first_uncraftable_item(creature);
        }
        else
        {
          int idx = tolower(d.at(0)) - 'a';
          auto f_it = crafting_functions.find(idx);

          if (f_it != crafting_functions.end())
          {
            auto f_p = f_it->second.first;
            kiln_used = (this->*f_p)(creature, tile);
          }
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

bool KilnManipulator::notify_on_first_uncraftable_item(CreaturePtr creature)
{
  for (const auto& cr_it : crafting_functions)
  {
    auto v_f = cr_it.second.second;

    if (!(this->*v_f)(creature))
    {
      return false;
    }
  }

  return true;
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

// JCD FIXME: Once Smithing is updated, move this into some CreatureUtils
// function.
bool KilnManipulator::verify_item_requirements(const vector<string>& component_item_ids, const string& crafted_item_id, const bool add_message, CreaturePtr creature)
{
  if (creature != nullptr)
  {
    Game& game = Game::instance();
    const ItemMap& items = game.get_items_ref();

    auto cr_it = items.find(crafted_item_id);
    ItemPtr crafted_item;

    if (cr_it == items.end() || cr_it->second == nullptr)
    {
      return false;
    }
    else
    {
      crafted_item = cr_it->second;
    }

    for (const string& comp_item_id : component_item_ids)
    {
      auto i_it = items.find(comp_item_id);

      if (i_it != items.end())
      {
        if (!creature->get_inventory()->has_item(comp_item_id))
        {
          if (add_message)
          {
            IMessageManager& mm_self = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

            mm_self.add_new_message(ActionTextKeys::get_kiln_no_item_message(i_it->second->get_usage_description_sid(), crafted_item->get_usage_description_sid()));
            mm_self.send();
          }

          return false;
        }
      }
      else
      {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool KilnManipulator::create_clay_item(ItemVerifier v, const vector<string>& component_item_ids, const string& crafted_item_id, const int rng_min, const int rng_max, CreaturePtr creature, TilePtr tile)
{
  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();
  const ItemMap& items = game.get_items_ref();
  auto cr_i_it = items.find(crafted_item_id);
  IMessageManager& mm_self = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  if (cr_i_it == items.end())
  {
    return false;
  }

  ItemPtr crafted_item_template = cr_i_it->second;

  if (!(this->*v)(creature))
  {
    return false;
  }

  for (const string& comp_item_id : component_item_ids)
  {
    auto i_it = items.find(comp_item_id);

    if (i_it != items.end())
    {
      if (!creature->get_inventory()->has_item(comp_item_id))
      {
        mm_self.add_new_message(ActionTextKeys::get_kiln_no_item_message(i_it->second->get_usage_description_sid(), crafted_item_template->get_usage_description_sid()));
        mm_self.send();

        return false;
      }
    }
    else
    {
      return false;
    }
  }

  vector<ItemPtr> selected_items;

  for (const string& comp_item_id : component_item_ids)
  {
    vector<ItemPtr> comp_items = creature->get_inventory()->get_all_from_base_id(comp_item_id);

    if (comp_items.size() == 1)
    {
      selected_items.push_back(comp_items[0]);
    }
    else
    {
      list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_base_id_filter(comp_item_id);
      ItemPtr selected_item = am.inventory(creature, creature->get_inventory(), display_filter_list, {}, false, false);

      if (selected_item != nullptr)
      {
        selected_items.push_back(selected_item);
      }
    }
  }

  // If we have an item for each component item ID, then we have everything
  // we need to make the new item.
  if (selected_items.size() == component_item_ids.size())
  {
    // Reduce or remove the selected items, create the new item, and put it
    // on the player's tile.
    create_item(creature, tile, selected_items, crafted_item_template, rng_min, rng_max);
  }

  return true;
}

bool KilnManipulator::verify_clay_pot(CreaturePtr creature)
{
  return verify_item_requirements({ ItemIdKeys::ITEM_ID_CLAY }, ItemIdKeys::ITEM_ID_CLAY_POT, true, creature);
}

bool KilnManipulator::verify_clay_shot(CreaturePtr creature)
{
  return verify_item_requirements({ ItemIdKeys::ITEM_ID_CLAY }, ItemIdKeys::ITEM_ID_CLAY_SHOT, true, creature);
}

bool KilnManipulator::verify_fire_bomb(CreaturePtr creature)
{
  return verify_item_requirements({ ItemIdKeys::ITEM_ID_CLAY, ItemIdKeys::ITEM_ID_MAGICI_SHARD }, ItemIdKeys::ITEM_ID_FIRE_BOMB, true, creature);
}

bool KilnManipulator::verify_shadow_bomb(CreaturePtr creature)
{
  return verify_item_requirements({ ItemIdKeys::ITEM_ID_CLAY, ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE }, ItemIdKeys::ITEM_ID_SHADOW_BOMB, true, creature);
}

bool KilnManipulator::create_clay_pot(CreaturePtr creature, TilePtr tile)
{
  return create_clay_item(&KilnManipulator::verify_clay_pot, { ItemIdKeys::ITEM_ID_CLAY }, ItemIdKeys::ITEM_ID_CLAY_POT, 1, 1, creature, tile);
}

bool KilnManipulator::create_clay_shot(CreaturePtr creature, TilePtr tile)
{
  return create_clay_item(&KilnManipulator::verify_clay_shot, { ItemIdKeys::ITEM_ID_CLAY }, ItemIdKeys::ITEM_ID_CLAY_SHOT, 12, 30, creature, tile);
}

bool KilnManipulator::create_fire_bomb(CreaturePtr creature, TilePtr tile)
{
  return create_clay_item(&KilnManipulator::verify_fire_bomb, { ItemIdKeys::ITEM_ID_CLAY, ItemIdKeys::ITEM_ID_MAGICI_SHARD }, ItemIdKeys::ITEM_ID_FIRE_BOMB, 3, 4, creature, tile);
}

bool KilnManipulator::create_shadow_bomb(CreaturePtr creature, TilePtr tile)
{
  return create_clay_item(&KilnManipulator::verify_shadow_bomb, { ItemIdKeys::ITEM_ID_CLAY, ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE }, ItemIdKeys::ITEM_ID_SHADOW_BOMB, 3, 4, creature, tile);
}

void KilnManipulator::create_item(CreaturePtr creature, TilePtr tile, vector<ItemPtr>& selected_items, ItemPtr item_template, const int rng_min, const int rng_max)
{
  if (creature != nullptr && tile != nullptr)
  {
    for (ItemPtr i : selected_items)
    {
      if (i != nullptr)
      {
        if (i->get_quantity() > 1)
        {
          i->set_quantity(i->get_quantity() - 1);
        }
        else
        {
          creature->get_inventory()->remove(i->get_id());
        }
      }
    }

    ItemStatus status = ItemStatus::ITEM_STATUS_UNCURSED;

    if (!selected_items.empty())
    {
      status = selected_items[RNG::range(0, selected_items.size() - 1)]->get_status();
    }

    ItemPtr item = ItemManager::create_item(item_template->get_base_id(), static_cast<uint>(RNG::range(rng_min, rng_max)));

    // Improve the item with free enchants based on crafting
    KilnCalculator kc;
    int enchants = RNG::range(kc.calc_min_free_enchants(creature), kc.calc_max_free_enchants(creature));
    item->enchant(kc.calc_pct_chance_brand(), enchants);

    if (item != nullptr)
    {
      item->set_status(status);
      tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
    }

    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KILN_CREATION_COMPLETE));
    manager.send();
  }
}
