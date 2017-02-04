#pragma once
#include "IActionManager.hpp"

class CurrencyAction : public IActionManager
{
  public:
    ActionCostValue count_currency(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};

