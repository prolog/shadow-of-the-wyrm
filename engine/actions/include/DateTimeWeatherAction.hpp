#pragma once
#include "IActionManager.hpp"

class DateTimeWeatherAction : public IActionManager
{
  public:
    ActionCostValue date_and_time_and_weather();

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    DateTimeWeatherAction();
};
