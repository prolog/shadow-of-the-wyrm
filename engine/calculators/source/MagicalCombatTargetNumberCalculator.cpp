#include "MagicalCombatTargetNumberCalculator.hpp"

MagicalCombatTargetNumberCalculator::MagicalCombatTargetNumberCalculator()
: CombatTargetNumberCalculator(AttackType::ATTACK_TYPE_MAGICAL)
{
}

// The target number for magical combat is the attacked creature's evade
// plus half the attacked creature's Awareness skill minus the attacker's
// Magic skill.
int MagicalCombatTargetNumberCalculator::calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  int target_number = 0;

  if (attacking_creature && attacked_creature)
  {
    Skills& d_skills = attacked_creature->get_skills();

    int defender_evade = attacked_creature->get_evade().get_current();
    int defender_awareness = (d_skills.get_value_incr_marks(SkillType::SKILL_GENERAL_AWARENESS) / 2);
    int attacker_magic_value = d_skills.get_value(SkillType::SKILL_GENERAL_MAGIC);

    target_number = defender_evade + defender_awareness - attacker_magic_value;

    if (target_number < 0) target_number = 0;
  }

  return target_number;
}

int MagicalCombatTargetNumberCalculator::calculate_pct_chance_pass_through_untargetted_square(CreaturePtr attacking_creature, CreaturePtr defending_creature)
{
  return 100;
}
