#pragma once
#include "IActionManager.hpp"

class AutomaticMovementAction : public IActionManager
{
  public:
    ActionCostValue automatic_movement(CreaturePtr creature) const;
    
  protected:
    friend class ActionManager;
    AutomaticMovementAction();
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
