#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "DigAction.hpp"
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
ActionCostValue DigAction::dig_through(CreaturePtr creature, MapPtr map, TilePtr adjacent_tile) const
{
  ActionCostValue acv =  0;

  if (creature != nullptr && map != nullptr && adjacent_tile != nullptr)
  {
    // Do the actual decomposition.

    // Copy over features
    
    // Copy over items

    acv = get_action_cost_value(creature);
  }

  return acv;
}


ActionCostValue DigAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
