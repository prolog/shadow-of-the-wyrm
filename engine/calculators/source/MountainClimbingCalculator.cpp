#include "MountainClimbingCalculator.hpp"
#include "RNG.hpp"

const int MountainClimbingCalculator::MAXIMUM_CLIMBING_TIME_MULTIPLIER = 6;
const int MountainClimbingCalculator::FALLING_CHANCE_MULTIPLIER = 7;

int MountainClimbingCalculator::calculate_max_mountain_climbing_time(const int mountaineering_skill_value) const
{
  int max_mountain_climbing_time = (mountaineering_skill_value * MAXIMUM_CLIMBING_TIME_MULTIPLIER);
  return max_mountain_climbing_time;
}

bool MountainClimbingCalculator::generate_does_fall_from_exhaustion(const int mountaineering_skill_value) const
{
  int val = RNG::range(1, mountaineering_skill_value * FALLING_CHANCE_MULTIPLIER);
  return (val == 1);
}

int MountainClimbingCalculator::generate_falling_damage() const
{
  int falling_damage = RNG::range(50, 150);
  return falling_damage;
}
