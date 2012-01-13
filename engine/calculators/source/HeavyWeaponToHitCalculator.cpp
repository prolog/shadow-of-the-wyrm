#include "HeavyWeaponToHitCalculator.hpp"

HeavyWeaponToHitCalculator::HeavyWeaponToHitCalculator()
{
}

int HeavyWeaponToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;

  if (creature)
  {
  }

  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/HeavyWeaponToHitCalculator_test.cpp"
#endif
