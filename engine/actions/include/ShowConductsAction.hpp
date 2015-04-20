#pragma once
#include <map>
#include "IActionManager.hpp"

class ShowConductsAction : public IActionManager
{
  public:
    ActionCostValue show_conducts(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
