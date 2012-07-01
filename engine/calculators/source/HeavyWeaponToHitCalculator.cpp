#include "HeavyWeaponToHitCalculator.hpp"

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
    int strength = creature->get_strength().get_current();
    int valour   = creature->get_strength().get_current();
    
    to_hit += (strength - 10) / 4;
    to_hit += (valour - 50) / 5;
  }

  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/HeavyWeaponToHitCalculator_test.cpp"
#endif
