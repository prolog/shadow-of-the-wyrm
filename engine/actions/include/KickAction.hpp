#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class KickAction : public IActionManager
{
  public:
    ActionCostValue kick(CreaturePtr creature);

  protected:
    friend class ActionManager;
    KickAction();
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
