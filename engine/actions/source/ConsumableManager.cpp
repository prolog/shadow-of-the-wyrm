#include "ConsumableManager.hpp"

// Consume a consumable, adding its nutrition to the hunger counter.
ActionCostValue ConsumableManager::consume(CreaturePtr creature, ConsumablePtr consumable)
{
  ActionCostValue action_cost_value = 0;

  if (creature && consumable)
  {
    HungerClock& hunger = creature->get_hunger_clock_ref();
    hunger.set_hunger(hunger.get_hunger() + consumable->get_nutrition());
  }

  return action_cost_value;
}

ActionCostValue ConsumableManager::get_action_cost_value() const
{
  return 1;
}

