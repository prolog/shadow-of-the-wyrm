#include "MagicToHitCalculator.hpp"

MagicToHitCalculator::MagicToHitCalculator()
: ToHitCalculator(ATTACK_TYPE_MAGICAL)
{
}

int MagicToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;

  if (creature)
  {
    int intelligence = creature->get_intelligence().get_current();
    int spirit       = creature->get_spirit().get_current();
    
    to_hit += (intelligence - 10) / 3;
    to_hit += (spirit - 50) / 5;
  }

  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicToHitCalculator_test.cpp"
#endif
