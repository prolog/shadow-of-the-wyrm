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

    bool eat_food(CreaturePtr creature, ItemPtr food);

    void add_food_message(CreaturePtr creature, ItemPtr food, const bool successfully_ate);

    ActionCostValue get_action_cost_value() const;
};

