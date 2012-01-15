#include "LightMeleeAndRangedWeaponToHitCalculator.hpp"

LightMeleeAndRangedWeaponToHitCalculator::LightMeleeAndRangedWeaponToHitCalculator()
{
}

int LightMeleeAndRangedWeaponToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;
  
  if (creature)
  {
    int dexterity = creature->get_dexterity().get_current();
    int valour    = creature->get_valour().get_current();
    
    to_hit += (dexterity - 10) / 3;
    to_hit += (valour - 50) / 5;
  }
  
  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/LightMeleeAndRangedWeaponToHitCalculator_test.cpp"
#endif
