#include "global_prototypes.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DigAction.hpp"
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
      bool dug = tm->dig(creature, map, tile);

      if (dug)
      {
        tile->set_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG, Bool::to_string(true));
        acv = get_action_cost_value(creature);
      }
    }
  }

  return acv;
}

// Dig through an adjacent tile.
ActionCostValue DigAction::dig_through(CreaturePtr creature, MapPtr map, TilePtr adjacent_tile, const Direction d) const
{
  ActionCostValue acv =  0;

  if (creature != nullptr && map != nullptr && adjacent_tile != nullptr)
  {
    IMessageManager& manager = MessageManagerFactory::instance();

    // Is there something preventing digging on this map?
    string no_dig = map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG);
    if (!no_dig.empty() && (String::to_bool(no_dig) == true))
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CANNOT_DIG));
      manager.send();

      return acv;
    }

    // Do the actual decomposition.
    TileGenerator tg;
    TilePtr new_tile = tg.generate(adjacent_tile->get_decomposition_tile_type());

    // Copy over features and items.
    new_tile->transformFrom(adjacent_tile);

    // Potentially add some items created by breaking up the original tile.
    ItemManager im;
    im.create_item_with_probability(DIG_PERCENT_CHANCE_ITEM, 100, new_tile->get_items(), adjacent_tile->get_decomposition_item_id(), static_cast<uint>(RNG::range(1, 6)));

    // Get the necessary details for re-adding
    Coordinate cr_loc = map->get_location(creature->get_id());
    Coordinate new_cr_loc = CoordUtils::get_new_coordinate(cr_loc, d);

    map->insert(new_cr_loc.first, new_cr_loc.second, new_tile);

    if (creature->get_is_player())
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_THROUGH_TILE));

      manager.send();
    }
    
    acv = get_action_cost_value(creature);
  }

  return acv;
}


ActionCostValue DigAction::get_action_cost_value(CreaturePtr creature) const
{
  return 20;
}
