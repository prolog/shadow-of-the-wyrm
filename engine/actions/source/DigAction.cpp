#include "global_prototypes.hpp"
#include "DigAction.hpp"
#include "TileManipulatorFactory.hpp"

using namespace std;

DigAction::DigAction()
{
}

// Dig on a particular tile.
ActionCostValue DigAction::dig(CreaturePtr creature, TilePtr tile) const
{
  ActionCostValue acv = 0;

  if (creature != nullptr && tile != nullptr)
  {
    TileManipulatorFactory tmf;
    ITileManipulatorPtr tm = tmf.create_tile_manipulator(tile);

    if (tm != nullptr)
    {
      bool dug = tm->dig(creature, tile);

      if (dug)
      {
        acv = get_action_cost_value(creature);
      }
    }
  }

  return acv;
}

ActionCostValue DigAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
