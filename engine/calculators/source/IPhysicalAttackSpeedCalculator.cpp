#include "IPhysicalAttackSpeedCalculator.hpp"
#include "NullSpeedCalculator.hpp"

ActionCostValue IPhysicalAttackSpeedCalculator::calculate(CreaturePtr creature)
{
  NullSpeedCalculator nsc;
  ActionCostValue action_cost_value = nsc.calculate(creature);

  if (creature)
  {
    if (has_weapon_equipped(creature))
    {
      action_cost_value = calculate_weapon_speed(creature);
    }
    else
    {
      action_cost_value = calculate_unarmed_attack_speed(creature);
    }
  }

  return action_cost_value;
}

ActionCostValue IPhysicalAttackSpeedCalculator::calculate_unarmed_attack_speed(CreaturePtr creature)
{
  NullSpeedCalculator nsc;
  return nsc.calculate(creature);
}

