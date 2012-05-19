#include "MagicalCombatTargetNumberCalculator.hpp"

MagicalCombatTargetNumberCalculator::MagicalCombatTargetNumberCalculator()
: CombatTargetNumberCalculator(ATTACK_TYPE_MAGICAL)
{
}

int MagicalCombatTargetNumberCalculator::calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  int target_number = 0;

  if (attacking_creature && attacked_creature)
  {
  }

  return target_number;
}
