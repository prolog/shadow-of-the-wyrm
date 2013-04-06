#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class SpellcastingAction : public IActionManager
{
  public:
    ActionCostValue cast_spell(CreaturePtr creature) const;
    
  protected:
    friend class ActionManager;
    SpellcastingAction();
    
    ActionCostValue get_action_cost_value() const;
};
