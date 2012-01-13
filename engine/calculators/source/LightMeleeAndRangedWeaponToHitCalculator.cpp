#include "LightMeleeAndRangedWeaponToHitCalculator.hpp"

LightMeleeAndRangedWeaponToHitCalculator::LightMeleeAndRangedWeaponToHitCalculator()
{
}

int LightMeleeAndRangedWeaponToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;
  
  if (creature)
  {
    
  }
  
  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/LightMeleeAndRangedWeaponToHitCalculator_test.cpp"
#endif
