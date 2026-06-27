#include "MountainClimbingCalculator.hpp"
#include "RNG.hpp"

const int MountainClimbingCalculator::MAXIMUM_CLIMBING_TIME_MULTIPLIER = 6;
const int MountainClimbingCalculator::FALLING_CHANCE_MULTIPLIER = 12;
const int MountainClimbingCalculator::PCT_CHANCE_PERCENTAGE_DAMAGE = 60;

int MountainClimbingCalculator::calculate_max_mountain_climbing_time(const int mountain_lore_skill_value, const bool is_incorporeal) const
{
  int max_mountain_climbing_time = (mountain_lore_skill_value * MAXIMUM_CLIMBING_TIME_MULTIPLIER);

  if (is_incorporeal)
  {
    max_mountain_climbing_time = std::numeric_limits<int>::max();
  }

  return max_mountain_climbing_time;
}

bool MountainClimbingCalculator::generate_does_fall_from_exhaustion(const int mountain_lore_skill_value, const bool is_incorporeal) const
{
  bool falls_from_exhaustion = (RNG::range(1, mountain_lore_skill_value * FALLING_CHANCE_MULTIPLIER) == 1);

  if (is_incorporeal)
  {
    falls_from_exhaustion = false;
  }

  return falls_from_exhaustion;
}

int MountainClimbingCalculator::generate_falling_damage(CreaturePtr creature) const
{
  int falling_damage = RNG::range(50, 150);

  if (RNG::percent_chance(PCT_CHANCE_PERCENTAGE_DAMAGE) && creature != nullptr)
  {
    falling_damage = std::min<int>(falling_damage, static_cast<int>(creature->get_hit_points().get_base() * 0.8f));
  }

  return falling_damage;
}
