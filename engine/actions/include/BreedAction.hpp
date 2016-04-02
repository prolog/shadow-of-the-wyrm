#pragma once
#include "IActionManager.hpp"

class BreedAction : public IActionManager
{
  public:
    ActionCostValue breed(CreaturePtr creature, MapPtr map) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    BreedAction();
};
