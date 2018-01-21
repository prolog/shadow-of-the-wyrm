#include "UntimedStatusCalculator.hpp"

int UntimedStatusCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  return std::numeric_limits<int>::max();
}

int UntimedStatusCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return 100;
}