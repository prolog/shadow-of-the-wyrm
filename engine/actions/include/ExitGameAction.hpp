#pragma once
#include "IActionManager.hpp"

class ExitGameAction : public IActionManager
{
  public:
    ActionCostValue save(CreaturePtr creature) const;
    ActionCostValue quit(CreaturePtr creature) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    ExitGameAction();
};
