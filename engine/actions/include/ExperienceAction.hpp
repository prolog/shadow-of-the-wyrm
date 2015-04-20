#pragma once
#include "IActionManager.hpp"

class ExperienceAction : public IActionManager
{
  public:
    ActionCostValue experience(CreaturePtr creature) const;
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    ExperienceAction();    
};
