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

// The chance for an untargetted melee or ranged attack to pass through
// an untargetted tile is the maximum of the attacking creature's archery
// skill and the defending creature's awareness.
int MeleeAndRangedCombatTargetNumberCalculator::calculate_pct_chance_pass_through_untargetted_square(CreaturePtr attacking_creature, CreaturePtr tile_creature)
{
  int pct_chance = 0;

  if (tile_creature != nullptr)
  {
    pct_chance = tile_creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_AWARENESS);
  }

  if (attacking_creature != nullptr)
  {
    pct_chance = std::max<int>(pct_chance, attacking_creature->get_skills().get_value(SkillType::SKILL_GENERAL_ARCHERY));
  }

  return pct_chance;
}