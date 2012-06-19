#pragma once
#include "IActionManager.hpp"

class DateTimeManager : public IActionManager
{
  public:
    ActionCostValue date_and_time();

  protected:
    friend class ActionManager;
    DateTimeManager();

    ActionCostValue get_action_cost_value() const;
};
