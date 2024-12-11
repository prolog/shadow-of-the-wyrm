#include "NullAttackSpeedCalculator.hpp"

// Assume 1 speed as a default for everything that is not defined.
ActionCostValue NullAttackSpeedCalculator::calculate(CreaturePtr /*creature*/)
{
  return 1;
}

