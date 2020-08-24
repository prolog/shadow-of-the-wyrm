#pragma once
#include "IActionManager.hpp"
#include "IMessageManager.hpp"

class OrderAction : public IActionManager
{
  public:
    ActionCostValue order(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

    ActionCostValue order_attack(CreaturePtr creature);
    ActionCostValue order_follow(CreaturePtr creature);
    ActionCostValue order_freeze(CreaturePtr creature);
    ActionCostValue order_at_ease(CreaturePtr creature);

    void set_order(CreaturePtr creature, const std::string& order_property, const std::string& value);

  protected:
    bool check_for_followers(CreaturePtr creature, IMessageManager& manager);

    void remove_orders(CreaturePtr creature);

    ActionCostValue order_followers(CreaturePtr creature, IMessageManager& manager);
};

