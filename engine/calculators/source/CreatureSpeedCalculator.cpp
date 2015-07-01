#include "CreatureSpeedCalculator.hpp"

int CreatureSpeedCalculator::calculate(CreaturePtr creature) const
{
  int calc_speed = 0;

  if (creature != nullptr)
  {
    Statistic speed = creature->get_speed();

    calc_speed = speed.get_base();
  }

  return calc_speed;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureSpeedCalculator_test.cpp"
#endif

