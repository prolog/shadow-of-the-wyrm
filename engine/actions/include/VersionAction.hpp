#pragma once
#include "IActionManager.hpp"

class VersionAction : public IActionManager
{
  public:
    ActionCostValue version() const;
    
  protected:
    friend class ActionManager;
    VersionAction();
    
    ActionCostValue get_action_cost_value() const override;
};
