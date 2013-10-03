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
    int nwp_bonus = get_combat_or_archery_bonus(creature);
    int dexterity = creature->get_dexterity().get_current();
    int weapon    = get_weapon_bonus(creature);
    int status    = get_status_bonus(creature);

    to_hit += nwp_bonus;
    to_hit += (dexterity - 10) / 3;
    to_hit +=  weapon;
    to_hit += status;
  }
  
  return to_hit;
}

int LightMeleeAndRangedWeaponToHitCalculator::get_combat_or_archery_bonus(CreaturePtr creature) const
{
  int bonus = 0;
  SkillType skill = SKILL_GENERAL_COMBAT;
  
  if (attack_type == ATTACK_TYPE_RANGED)
  {
    skill = SKILL_GENERAL_ARCHERY;
  }
  
  bonus = skill / NWP_SKILL_BONUS_DIVISOR;
  
  return bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/LightMeleeAndRangedWeaponToHitCalculator_test.cpp"
#endif
