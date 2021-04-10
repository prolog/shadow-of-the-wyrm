#pragma once
#include "IActionManager.hpp"

class AutomaticActionsAction : public IActionManager
{
  public:
    ActionCostValue automatic_actions() const;
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};

