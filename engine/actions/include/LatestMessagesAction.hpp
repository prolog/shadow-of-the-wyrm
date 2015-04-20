#pragma once
#include <map>
#include "IActionManager.hpp"

class LatestMessagesAction : public IActionManager
{
  public:
    ActionCostValue latest_messages(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
