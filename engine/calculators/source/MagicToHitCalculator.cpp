#include "MagicToHitCalculator.hpp"

MagicToHitCalculator::MagicToHitCalculator()
{
}

int MagicToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;

  if (creature)
  {
  }

  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicToHitCalculator_test.cpp"
#endif
