#pragma once
#include "IActionManager.hpp"

class DateTimeAction : public IActionManager
{
  public:
    ActionCostValue date_and_time();

  protected:
    friend class ActionManager;
    DateTimeAction();

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
