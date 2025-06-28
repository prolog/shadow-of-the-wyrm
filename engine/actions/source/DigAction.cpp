#include "global_prototypes.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DigAction.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "IFeatureManipulatorFactory.hpp"
#include "ItemBreakageCalculator.hpp"
#include "ItemIdentifier.hpp"
#include "ItemManager.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MaterialFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "StatisticsMarker.hpp"
#include "TextMessages.hpp"
#include "TileGenerator.hpp"
#include "TileManipulatorFactory.hpp"

using namespace std;

const int DigAction::DIG_PERCENT_CHANCE_MARK_STATISTIC = 15;

DigAction::DigAction()
{
}

// Knock a few stones loose on and around a particular tile
ActionCostValue DigAction::dig_ceiling(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && map != nullptr)
  {
    auto tile_map = MapUtils::get_adjacent_and_creature_tiles(map, creature);
    for (auto& t_pair : tile_map)
    {
      TilePtr tile = t_pair.second;

      if (tile != nullptr && !tile->get_is_blocking_for_item() && RNG::percent_chance(75))
      {
        string item_id = ItemIdKeys::ITEM_ID_STONE;

        if (RNG::percent_chance(25))
        {
          item_id = ItemIdKeys::ITEM_ID_ROCK;
        }

        ItemPtr item = ItemManager::create_item(item_id, RNG::range(1, 4));
        tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
      }
    }

    IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CEILING));

    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

// Dig on a particular tile.
ActionCostValue DigAction::dig_within(CreaturePtr creature, ItemPtr dig_item, MapPtr map, TilePtr tile) const
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && tile != nullptr)
  {
    TileManipulatorFactory tmf;
    ITileManipulatorPtr tm = tmf.create_tile_manipulator(tile);

    if (tm != nullptr)
    {
      TileSuperType tst = tile->get_tile_super_type();

      bool added_msg = add_cannot_dig_message_if_necessary(creature, map, tile);
      if (added_msg) return acv;

      if (tile_super_type_supports_digging(tst))
      {
        if (tm->dig(creature, map, tile))
        {
          handle_potential_item_breakage(creature, tile, dig_item);

          tile->set_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG, std::to_string(true));
          acv = get_action_cost_value(creature);

          // Digging also removes any seeds currently planted.
          // Useful for when you wanted a lovely orchard full of cherry trees,
          // but you accidentally planted a pear seed.  How embarassing!
          tile->remove_additional_property(TileProperties::TILE_PROPERTY_PLANTED);

          // Regular digging (ground, shovel - the kind that Heaney avoided) 
          // has a chance to train Strength.
          if (RNG::percent_chance(DIG_PERCENT_CHANCE_MARK_STATISTIC))
          {
            StatisticsMarker sm;
            sm.mark_strength(creature);
          }
        }
      }
      else
      {
        add_cannot_dig_on_tile_super_type_message(creature);
      }
    }
  }

  return acv;
}

// Dig through an adjacent tile.
ActionCostValue DigAction::dig_through(const string& creature_id, ItemPtr dig_item, MapPtr map, TilePtr adjacent_tile, const Coordinate& dig_coord, const bool add_messages, const bool dig_tile_only) const
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (map != nullptr && adjacent_tile != nullptr)
  {
    CreaturePtr creature = map->get_creature(creature_id);

    if (add_messages)
    {
      bool added_msg = add_cannot_dig_message_if_necessary(creature, map, adjacent_tile);
      if (added_msg) return acv;

      bool confirm = add_shop_confirmation_message_if_necessary(creature, map, dig_coord);
      if (!confirm) return acv;
    }

    // If we're digging into a shop, that is not appreciated, not at all.
    MapUtils::anger_shopkeeper_if_necessary(dig_coord, map, creature);

    // Do the actual decomposition, then re-add the tile, check for dig item
    // breakage, and add an appropriate message.
    if (add_messages)
    {
      add_successful_dig_message(creature, adjacent_tile);
    }

    TilePtr new_tile = dig_tile(creature, adjacent_tile, dig_tile_only);
    map->insert(dig_coord, new_tile);

    handle_potential_item_breakage(creature, adjacent_tile, dig_item);

    // Digging through a tile is strenuous, and always trains Strength.
    // Assuming, of course, the character is using an item and this isn't part
    // of a spell.
    if (dig_item != nullptr)
    {
      StatisticsMarker sm;
      sm.mark_strength(creature);
    }

    Game::instance().get_sound()->play(SoundEffectID::DIG);
    acv = get_action_cost_value(creature);
  }

  return acv;
}

bool DigAction::add_cannot_dig_message_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile) const
{
  bool added_msg = false;
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  string map_flag;
  string tile_flag;

  if (map != nullptr)
  {
    map_flag = map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG);
  }

  if (tile != nullptr)
  {
    tile_flag = tile->get_additional_property(TileProperties::TILE_PROPERTY_CANNOT_DIG);
  }

  vector<string> dig_flags = {map_flag, tile_flag};

  for (const string& dig_flag : dig_flags)
  {
    if (!dig_flag.empty() && (String::to_bool(dig_flag) == true))
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CANNOT_DIG));
      manager.send();

      added_msg = true;
      break;
    }
  }

  return added_msg;
}

// By digging the tile, we create a new one using the decomposition tile
// type, and potentially add items (e.g., rocks, earth) using the decomposition
// item id.
TilePtr DigAction::dig_tile(CreaturePtr creature, TilePtr adjacent_tile, const bool dig_tile_only) const
{
  TileGenerator tg;

  TileType decomp_tile_type = adjacent_tile->get_decomposition_tile_type();

  if (adjacent_tile != nullptr && !dig_tile_only)
  {
    MapPtr current_map = Game::instance().get_current_map();

    // First, dig through any features.
    bool dug_feature = dig_feature(creature, current_map, adjacent_tile);

    // Next, dig through any items.
    bool dug_items = dig_items(adjacent_tile->get_items());

    if (dug_feature || dug_items)
    {
      // Always add these messages, so that the player knows that stone items
      // or features were destroyed.
      add_stone_dust_message(creature);
    }
  }

  // Finally dig through the tile itself.
  if (decomp_tile_type != TileType::TILE_TYPE_UNDEFINED)
  {
    TilePtr new_tile = tg.generate(decomp_tile_type);

    // Copy over features and items.
    new_tile->transform_from(adjacent_tile);

    // Potentially add some items created by breaking up the original tile.
    ItemManager im;
    vector<pair<pair<int, int>, string>> decomp_details = adjacent_tile->get_decomposition_item_ids();

    // For each item that can potentially be generated, check to see if it's
    // created.
    for (const auto& item_pair : decomp_details)
    {
      if (RNG::x_in_y_chance(item_pair.first.first, item_pair.first.second))
      {
        ItemPtr item = ItemManager::create_item(item_pair.second, static_cast<uint>(RNG::range(1, 6)));
        new_tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }
    }

    return new_tile;
  }
  else
  {
    return adjacent_tile;
  }
}

bool DigAction::dig_feature(CreaturePtr creature, MapPtr map, TilePtr tile) const
{
  bool dug = false;

  if (tile != nullptr && tile->has_feature())
  {
    FeaturePtr feature = tile->get_feature();
    MaterialPtr mat = MaterialFactory::create_material(feature->get_material_type());

    if (mat != nullptr && mat->get_crumbles())
    {
      FeatureManipulatorPtr manip = IFeatureManipulatorFactory::create_manipulator(feature);
      manip->desecrate(creature, map);
      tile->remove_feature();

      dug = true;
    }
  }
  
  return dug;
}

bool DigAction::dig_items(IInventoryPtr items) const
{
  bool dug = false;

  if (items != nullptr)
  {
    list<ItemPtr>& raw_items = items->get_items_ref();
    size_t original_size = raw_items.size();

    raw_items.remove_if([](ItemPtr i)
      {
        MaterialPtr m = MaterialFactory::create_material(i->get_material_type());
        return (m != nullptr && m->get_crumbles() && !i->get_artifact());
      });

    size_t new_size = raw_items.size();
    dug = (new_size < original_size);
  }

  return dug;
}

void DigAction::add_successful_dig_message(CreaturePtr creature, TilePtr adjacent_tile) const
{
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  if (adjacent_tile != nullptr && creature != nullptr && creature->get_is_player())
  {
    string msg_sid = adjacent_tile->get_dig_message_sid();

    if (msg_sid.empty())
    {
      msg_sid = ActionTextKeys::ACTION_DIG_THROUGH_TILE;
    }

    manager.add_new_message(StringTable::get(msg_sid));
    manager.send();
  }
}

void DigAction::add_stone_dust_message(CreaturePtr creature) const
{
  IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

  if (creature->get_is_player())
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_STONE_DUST));
    manager.send();
  }
}

void DigAction::add_cannot_dig_on_tile_super_type_message(CreaturePtr creature) const
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CANNOT_DIG_ON_SUPER_TYPE));
    manager.send();
  }
}

void DigAction::handle_potential_item_breakage(CreaturePtr creature, TilePtr adjacent_tile, ItemPtr item) const
{
  if (creature != nullptr && item != nullptr)
  {
    // Did the item break?
    ItemBreakageCalculator ibc;
    if (RNG::percent_chance(ibc.calculate_pct_chance_digging_breakage(creature, adjacent_tile, item)))
    {
      creature->get_equipment().remove_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

      ItemIdentifier iid;
      IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
      manager.add_new_message(ActionTextKeys::get_item_breakage_message(creature->get_description_sid(), creature->get_is_player(), iid.get_appropriate_description(item)));
      manager.send();
    }
  }
}

// JCD FIXME: If there get to be more and more checks surrounding tile super type,
// consider making it a class based on the existing enum, with member functions
// like the one below.
bool DigAction::tile_super_type_supports_digging(const TileSuperType tst) const
{
  return (tst == TileSuperType::TILE_SUPER_TYPE_GROUND);
}

bool DigAction::add_shop_confirmation_message_if_necessary(CreaturePtr creature, MapPtr map, const Coordinate& dig_coord) const
{
  bool confirm = true;

  if (creature != nullptr && map != nullptr)
  {
    pair<bool, string> shop_adj = MapUtils::is_in_shop_or_adjacent(map, dig_coord);
    
    if (shop_adj.first)
    {
      IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(ActionTextKeys::ACTION_DIG_SHOP));
      manager.send();

      confirm = creature->get_decision_strategy()->get_confirmation();
    }
  }

  return confirm;
}
ActionCostValue DigAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 20;
}
