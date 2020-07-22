#pragma once
#include "IActionManager.hpp"
#include "IMessageManager.hpp"

class OrderAction : public IActionManager
{
  public:
    ActionCostValue order(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    bool check_for_skills(CreaturePtr creature, IMessageManager& manager);
    bool check_for_followers(CreaturePtr creature, IMessageManager& manager);

    ActionCostValue order_followers(CreaturePtr creature, IMessageManager& manager);
};

