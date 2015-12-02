#include "TertiaryUnarmedCalculator.hpp"

// The chance to knock back via a kick or other tertiary attack is equal
// to half the creature's current strength.
int TertiaryUnarmedCalculator::calculate_knock_back_pct_chance(CreaturePtr creature)
{
  int chance = 0;

  if (creature != nullptr)
  {
    Statistic strength = creature->get_strength();

    chance = strength.get_current() / 2;
  }

  return chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/TertiaryUnarmedCalculator_test.cpp"
#endif

