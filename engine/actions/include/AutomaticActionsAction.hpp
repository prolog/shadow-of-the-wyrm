#pragma once
#include "IActionManager.hpp"

class AutomaticActionsAction : public IActionManager
{
  public:
    std::map<int, std::pair<std::string, std::string>> get_auto_action_settings() const;
    ActionCostValue automatic_actions() const;
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};

