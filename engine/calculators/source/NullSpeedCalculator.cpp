#include "NullSpeedCalculator.hpp"

// Assume 1 speed as a default for everything that is not defined.
ActionCostValue NullSpeedCalculator::calculate(CreaturePtr creature)
{
  return 1;
}

