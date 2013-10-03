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
    SkillManager sm;
    
    int combat   = sm.get_skill_value(creature, SKILL_GENERAL_COMBAT);
    int strength = creature->get_strength().get_current();
    int weapon   = get_weapon_bonus(creature);
    int status   = get_status_bonus(creature);
    
    to_hit += combat / NWP_SKILL_BONUS_DIVISOR;
    to_hit += (strength - 10) / 4;
    to_hit += weapon;
    to_hit += status;
  }

  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/HeavyWeaponToHitCalculator_test.cpp"
#endif
