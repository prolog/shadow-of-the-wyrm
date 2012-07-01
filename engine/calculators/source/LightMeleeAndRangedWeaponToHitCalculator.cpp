#include "LightMeleeAndRangedWeaponToHitCalculator.hpp"

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
    int dexterity = creature->get_dexterity().get_current();
    int valour    = creature->get_valour().get_current();
    int weapon    = get_weapon_bonus(creature);
    
    to_hit += (dexterity - 10) / 3;
    to_hit += (valour - 50) / 5;
    to_hit +=  weapon;
  }
  
  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/LightMeleeAndRangedWeaponToHitCalculator_test.cpp"
#endif
