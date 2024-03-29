#include "LightMeleeAndRangedWeaponToHitCalculator.hpp"
#include "SkillManager.hpp"

LightMeleeAndRangedWeaponToHitCalculator::LightMeleeAndRangedWeaponToHitCalculator()
: ToHitCalculator()
{
}

LightMeleeAndRangedWeaponToHitCalculator::LightMeleeAndRangedWeaponToHitCalculator(const AttackType new_attack_type)
: ToHitCalculator(new_attack_type)
{
}

int LightMeleeAndRangedWeaponToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;
  
  if (creature)
  {
    to_hit = creature->get_to_hit().get_current();

    int nwp_bonus = get_combat_or_archery_bonus(creature);
    int dexterity = get_statistic(creature).get_current();
    int level     = get_level_bonus(creature);
    int weapon    = get_weapon_bonus(creature);
    int modifier  = get_modifier_bonus(creature);
    int skill     = get_skills_bonus(creature);
    int status    = get_status_bonus(creature);
    int bac_modifier = static_cast<int>(creature->get_blood().get_blood_alcohol_content() * 100);

    to_hit += nwp_bonus;
    to_hit += (dexterity - 10) / 3;
    to_hit += level;
    to_hit += weapon;
    to_hit += modifier;
    to_hit += skill;
    to_hit += status;
    to_hit -= bac_modifier;
  }
  
  return to_hit;
}

Statistic& LightMeleeAndRangedWeaponToHitCalculator::get_statistic(CreaturePtr creature)
{
  return creature->get_dexterity_ref();
}

int LightMeleeAndRangedWeaponToHitCalculator::get_combat_or_archery_bonus(CreaturePtr creature) const
{
  int bonus = 0;
  SkillType skill = SkillType::SKILL_GENERAL_COMBAT;
  
  if (attack_type == AttackType::ATTACK_TYPE_RANGED)
  {
    skill = SkillType::SKILL_GENERAL_ARCHERY;
  }

  if (creature != nullptr)
  {
    bonus = static_cast<int>(creature->get_skills().get_value(skill)) / NWP_SKILL_BONUS_DIVISOR;
  }
  
  return bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/LightMeleeAndRangedWeaponToHitCalculator_test.cpp"
#endif
