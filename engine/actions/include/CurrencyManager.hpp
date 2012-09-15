#pragma once
#include "IActionManager.hpp"

class CurrencyManager
{
  public:
    ActionCostValue count_currency(CreaturePtr creature);

  protected:
    void add_currency_message_if_necessary(CreaturePtr creature, const uint currency_amount);
    ActionCostValue get_action_cost_value() const;
};

