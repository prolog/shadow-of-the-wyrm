#include "global_prototypes.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DigAction.hpp"
#include "MessageManagerFactory.hpp"
#include "TileGenerator.hpp"
#include "TileManipulatorFactory.hpp"

using namespace std;

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
    // Do the actual decomposition.
    TileGenerator tg;
    TilePtr new_tile = tg.generate(adjacent_tile->get_decomposition_tile_type());

    // Copy over features and items.
    new_tile->transformFrom(adjacent_tile);

    // Get the necessary details for re-adding
    Coordinate cr_loc = map->get_location(creature->get_id());
    Coordinate new_cr_loc = CoordUtils::get_new_coordinate(cr_loc, d);

    map->insert(new_cr_loc.first, new_cr_loc.second, new_tile);

    if (creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();
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
