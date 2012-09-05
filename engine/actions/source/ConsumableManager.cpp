#include "ConsumableManager.hpp"

ActionCostValue ConsumableManager::consume(CreaturePtr creature, ConsumablePtr consumable)
{
  ActionCostValue action_cost_value = 0;

  if (creature && consumable)
  {
    // ... do nutrition counter stuff here ...
  }

  return action_cost_value;
}

ActionCostValue ConsumableManager::get_action_cost_value() const
{
  return 1;
}

