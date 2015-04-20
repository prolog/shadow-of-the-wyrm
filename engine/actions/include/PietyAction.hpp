#pragma once
#include "IActionManager.hpp"

class PietyAction : public IActionManager
{
  public:
    ActionCostValue piety(CreaturePtr creature, ActionManager * const am) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    PietyAction();    
};
