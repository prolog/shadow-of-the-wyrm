#include "CreatureSpeedCalculator.hpp"
#include "CarryingCapacityCalculator.hpp"

const float CreatureSpeedCalculator::BURDENED_SPEED_MULTIPLIER = 1.20f;
const float CreatureSpeedCalculator::STRAINED_SPEED_MULTIPLIER = 1.5f;

int CreatureSpeedCalculator::calculate(CreaturePtr creature) const
{
  int calc_speed = 0;

  if (creature != nullptr)
  {
    Statistic speed = creature->get_speed();
    calc_speed = speed.get_base();

    Weight total_weight = creature->get_weight_carried();
    uint weight_in_oz = total_weight.get_weight();

    float multiplier = 1.0;
    CarryingCapacityCalculator ccc;

    if (weight_in_oz >= ccc.calculate_strained_weight(creature))
    {
      multiplier = STRAINED_SPEED_MULTIPLIER;
    }
    else if (weight_in_oz >= ccc.calculate_burdened_weight(creature))
    {
      multiplier = BURDENED_SPEED_MULTIPLIER;
    }

    calc_speed = static_cast<int>(calc_speed * multiplier);
  }

  return calc_speed;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureSpeedCalculator_test.cpp"
#endif

