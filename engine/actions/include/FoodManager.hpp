#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class FoodManager
{
  public:
    ActionCostValue eat(CreaturePtr creature, ActionManager * const am);

  protected:
    friend class ActionManager;
    FoodManager();

    ActionCostValue get_action_cost_value() const;
};

