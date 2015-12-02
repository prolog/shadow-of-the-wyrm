#include "global_prototypes.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DigAction.hpp"
#include "ItemBreakageCalculator.hpp"
#include "ItemIdentifier.hpp"
#include "ItemManager.hpp"
#include "MapProperties.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"
#include "TileManipulatorFactory.hpp"

using namespace std;

const int DigAction::DIG_PERCENT_CHANCE_ITEM = 8;

DigAction::DigAction()
{
}

// Dig on a particular tile.
ActionCostValue DigAction::dig_within(CreaturePtr creature, MapPtr map, TilePtr tile) const
{
  ActionCostValue acv = 0;

  if (creature != nullptr && tile != nullptr)
  {
    TileManipulatorFactory tmf;
    ITileManipulatorPtr tm = tmf.create_tile_manipulator(tile);

    if (tm != nullptr)
    {
      TileSuperType tst = tile->get_tile_super_type();

      if (tile_super_type_supports_digging(tst))
      {
        if (tm->dig(creature, map, tile))
        {
          tile->set_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG, Bool::to_string(true));
          acv = get_action_cost_value(creature);

          // Digging also removes any seeds currently planted.
          // Useful for when you wanted a lovely orchard full of cherry trees,
          // but you accidentally planted a pear seed.  How embarassing!
          tile->remove_additional_property(TileProperties::TILE_PROPERTY_PLANTED);
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
ActionCostValue DigAction::dig_through(CreaturePtr creature, ItemPtr dig_item, MapPtr map, TilePtr adjacent_tile, const Direction d) const
{
  ActionCostValue acv =  0;

  if (creature != nullptr && map != nullptr && adjacent_tile != nullptr)
  {
    bool added_msg = add_cannot_dig_message_if_necessary(creature, map);
    if (added_msg) return acv;

    // Do the actual decomposition, then re-add the tile, check for dig item
    // breakage, and add an appropriate message.
    TilePtr new_tile = dig_tile(adjacent_tile);
    add_new_tile_to_dig_location(new_tile, map, creature->get_id(), d);
    add_successful_dig_message(creature);
    handle_potential_item_breakage(creature, dig_item);

    acv = get_action_cost_value(creature);
  }

  return acv;
}

bool DigAction::add_cannot_dig_message_if_necessary(CreaturePtr creature, MapPtr map) const
{
  bool added_msg = false;
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  // Is there something preventing digging on this map?
  string no_dig = map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG);
  if (!no_dig.empty() && (String::to_bool(no_dig) == true))
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CANNOT_DIG));
    manager.send();

    added_msg = true;
  }

  return added_msg;
}

// By digging the tile, we create a new one using the decomposition tile
// type, and potentially add items (e.g., rocks, earth) using the decomposition
// item id.
TilePtr DigAction::dig_tile(TilePtr adjacent_tile) const
{
  TileGenerator tg;
  TilePtr new_tile = tg.generate(adjacent_tile->get_decomposition_tile_type());

  // Copy over features and items.
  new_tile->transform_from(adjacent_tile);

  // Potentially add some items created by breaking up the original tile.
  ItemManager im;
  im.create_item_with_probability(DIG_PERCENT_CHANCE_ITEM, 100, new_tile->get_items(), adjacent_tile->get_decomposition_item_id(), static_cast<uint>(RNG::range(1, 6)));

  return new_tile;
}

void DigAction::add_new_tile_to_dig_location(TilePtr new_tile, MapPtr map, const std::string& creature_id, const Direction d) const
{
  // Get the necessary details for re-adding
  Coordinate cr_loc = map->get_location(creature_id);
  Coordinate new_cr_loc = CoordUtils::get_new_coordinate(cr_loc, d);

  map->insert(new_cr_loc.first, new_cr_loc.second, new_tile);
}

void DigAction::add_successful_dig_message(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (creature->get_is_player())
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_THROUGH_TILE));
    manager.send();
  }
}

void DigAction::add_cannot_dig_on_tile_super_type_message(CreaturePtr creature) const
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CANNOT_DIG_ON_SUPER_TYPE));
    manager.send();
  }
}

void DigAction::handle_potential_item_breakage(CreaturePtr creature, ItemPtr item) const
{
  if (creature != nullptr && item != nullptr)
  {
    // Did the item break?
    ItemBreakageCalculator ibc;
    if (RNG::percent_chance(ibc.calculate_pct_chance_digging_breakage(item)))
    {
      creature->get_equipment().remove_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

      ItemIdentifier iid;
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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

ActionCostValue DigAction::get_action_cost_value(CreaturePtr creature) const
{
  return 20;
}
