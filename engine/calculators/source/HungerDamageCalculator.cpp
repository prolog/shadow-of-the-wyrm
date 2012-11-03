#include "HungerDamageCalculator.hpp"

const int HungerDamageCalculator::HUNGER_DAMAGE_PER_TICK = 10;

int HungerDamageCalculator::calculate_hunger_damage(CreaturePtr creature, const ulonglong num_ticks) const
{
  return static_cast<int>(num_ticks * HUNGER_DAMAGE_PER_TICK);
}

#ifdef UNIT_TESTS
#include "unit_tests/HungerDamageCalculator_test.cpp"
#endif