#include "MagicalAttackSpeedCalculator.hpp"
#include "NullSpeedCalculator.hpp"

ActionCostValue MagicalAttackSpeedCalculator::calculate(CreaturePtr creature)
{
  NullSpeedCalculator nsc;
  ActionCostValue action_cost_value = nsc.calculate(creature);

  if (creature)
  {
  }

  return action_cost_value;
}
