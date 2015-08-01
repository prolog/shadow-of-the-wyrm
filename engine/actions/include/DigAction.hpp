#pragma once
#include "IActionManager.hpp"

class DigAction : public IActionManager
{
  public:
    ActionCostValue dig(CreaturePtr creature, MapPtr map, TilePtr tile) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class StairwayMovementAction;
    DigAction();
};
