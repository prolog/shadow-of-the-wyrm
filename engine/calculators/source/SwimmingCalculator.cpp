#include <algorithm>
#include "SwimmingCalculator.hpp"

const int SwimmingCalculator::MAXIMUM_SWIMMING_TIME_MULTIPLIER = 6;
const float SwimmingCalculator::SWIMMING_DAMAGE_MAX_HP_MULTIPLIER = 0.10f;

int SwimmingCalculator::calculate_maximum_swimming_time(const int swimming_skill_value) const
{
  return swimming_skill_value * MAXIMUM_SWIMMING_TIME_MULTIPLIER;
}

// Swimming damage is always 10% of total HP.
int SwimmingCalculator::calculate_swimming_damage(CreaturePtr creature) const
{
  int swimming_damage = 0;
  
  if (creature)
  {
    Statistic hit_points = creature->get_hit_points();    
    swimming_damage = static_cast<int>(std::max(1.0f, static_cast<float>(hit_points.get_base()) * SWIMMING_DAMAGE_MAX_HP_MULTIPLIER));
  }
  
  return swimming_damage;
}
