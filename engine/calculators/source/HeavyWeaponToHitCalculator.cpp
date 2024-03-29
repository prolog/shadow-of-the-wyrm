#include "HeavyWeaponToHitCalculator.hpp"
#include "SkillManager.hpp"

HeavyWeaponToHitCalculator::HeavyWeaponToHitCalculator()
{
}

HeavyWeaponToHitCalculator::HeavyWeaponToHitCalculator(const AttackType new_attack_type)
: ToHitCalculator(new_attack_type)
{
}

int HeavyWeaponToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;

  if (creature)
  {
    to_hit = creature->get_to_hit().get_current();

    SkillManager sm;
    
    int combat   = sm.get_skill_value(creature, SkillType::SKILL_GENERAL_COMBAT);
    int strength = get_statistic(creature).get_current();
    int level    = get_level_bonus(creature);
    int weapon   = get_weapon_bonus(creature);
    int modifier = get_modifier_bonus(creature);
    int skills   = get_skills_bonus(creature);
    int status   = get_status_bonus(creature);

    // There is no BAC penalty for heavy weapons - unlike light and ranged
    // weapons, which rely on finesse, heavy weapons rely more on strength,
    // and so are unaffected by the loss of fine motor control due to 
    // drunkenness.

    to_hit += combat / NWP_SKILL_BONUS_DIVISOR;
    to_hit += (strength - 10) / 4;
    to_hit += level;
    to_hit += weapon;
    to_hit += modifier;
    to_hit += skills;
    to_hit += status;
  }

  return to_hit;
}

Statistic& HeavyWeaponToHitCalculator::get_statistic(CreaturePtr creature)
{
  return creature->get_strength_ref();
}

#ifdef UNIT_TESTS
#include "unit_tests/HeavyWeaponToHitCalculator_test.cpp"
#endif
