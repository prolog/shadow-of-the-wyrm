#pragma once
#include "IActionManager.hpp"

class PietyAction : public IActionManager
{
  public:
    ActionCostValue piety(CreaturePtr creature, ActionManager * const am) const;
    
  protected:
    friend class ActionManager;
    PietyAction();
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
