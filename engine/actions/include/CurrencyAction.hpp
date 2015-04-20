#pragma once
#include "IActionManager.hpp"

class CurrencyAction : public IActionManager
{
  public:
    ActionCostValue count_currency(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    void add_currency_message_if_necessary(CreaturePtr creature, const uint currency_amount);
};

