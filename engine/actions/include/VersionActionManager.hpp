#pragma once
#include "IActionManager.hpp"

class VersionActionManager : public IActionManager
{
  public:
    ActionCostValue version() const;
    
  protected:
    friend class ActionManager;
    VersionActionManager();
    
    ActionCostValue get_action_cost_value() const;
};
