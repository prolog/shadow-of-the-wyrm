#pragma once
#include "IActionManager.hpp"

class HelpAction : public IActionManager
{
  public:
    ActionCostValue help(CreaturePtr creature) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    HelpAction();
};
