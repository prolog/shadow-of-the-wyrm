#pragma once
#include "IActionManager.hpp"

class VersionAction : public IActionManager
{
  public:
    ActionCostValue version() const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    VersionAction();
};
