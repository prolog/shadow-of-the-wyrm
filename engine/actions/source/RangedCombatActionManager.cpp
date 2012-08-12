#include "RangedCombatActionManager.hpp"

RangedCombatActionManager::RangedCombatActionManager()
{
}

ActionCostValue RangedCombatActionManager::fire_missile(CreaturePtr creature)
{
  return get_action_cost_value();
}

ActionCostValue RangedCombatActionManager::get_action_cost_value() const
{
  return 1;
}
