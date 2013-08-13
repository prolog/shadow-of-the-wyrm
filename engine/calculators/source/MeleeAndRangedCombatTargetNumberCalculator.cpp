#include "MeleeAndRangedCombatTargetNumberCalculator.hpp"
#include "WeaponDifficultyCalculator.hpp"

MeleeAndRangedCombatTargetNumberCalculator::MeleeAndRangedCombatTargetNumberCalculator(const AttackType new_attack_type)
: CombatTargetNumberCalculator(new_attack_type)
{
}

// The target number:
//
// = the difficulty of the attacking creature's weapon
// + attacked creature's evade
//
int MeleeAndRangedCombatTargetNumberCalculator::calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  int target_number = 0;

  if (attacking_creature && attacked_creature)
  {
    WeaponDifficultyCalculator wdc;
    int weapon_difficulty = wdc.calculate_base_difficulty(attacking_creature, attack_type);
    int target_evade = attacked_creature->get_evade().get_current();
    
    target_number = weapon_difficulty + target_evade;
  }

  return target_number;
}
