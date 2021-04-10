#pragma once
#include "IActionManager.hpp"

class AutomaticActionsAction : public IActionManager
{
  public:
    std::vector<std::pair<std::string, std::string>> get_auto_action_settings(CreaturePtr creature) const;
    ActionCostValue automatic_actions(CreaturePtr creature) const;
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};

