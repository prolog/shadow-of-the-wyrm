#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class RangedCombatActionManager : public IActionManager
{
  public:
    ActionCostValue fire_missile(CreaturePtr creature);

  protected:
    friend class ActionManager;
    RangedCombatActionManager();

    ActionCostValue get_action_cost_value() const;
};
