#pragma once
#include "IActionManager.hpp"

class DigAction : public IActionManager
{
  public:
    // Dig within an existing tile.  Eg, dig up a grave, a barrow, etc.
    ActionCostValue dig_within(CreaturePtr creature, MapPtr map, TilePtr tile) const;

    // Dig through an adjacent tile - break up the tile into another type.
    // Eg, rock should become rocky earth, earth should become floor, etc.
    ActionCostValue dig_through(CreaturePtr creature, MapPtr map, TilePtr adjacent_tile) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class StairwayMovementAction;
    friend class MovementAction;

    DigAction();
};
