#include "DefaultStatusEffectCalculator.hpp"

int DefaultStatusEffectCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return 0;
}

int DefaultStatusEffectCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  return 0;
}

#ifdef UNIT_TESTS
#include "unit_tests/DefaultStatusEffectCalculator_test.cpp"
#endif