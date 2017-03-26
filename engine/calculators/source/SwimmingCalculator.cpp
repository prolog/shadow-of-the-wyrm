#include <algorithm>
#include "SwimmingCalculator.hpp"

using namespace std;

const int SwimmingCalculator::MAXIMUM_SWIMMING_TIME_MULTIPLIER = 6;
const float SwimmingCalculator::SWIMMING_DAMAGE_MAX_HP_MULTIPLIER = 0.10f;
const int SwimmingCalculator::HOLD_BREATH_HEALTH_DIVISOR = 3;

int SwimmingCalculator::calculate_maximum_swimming_time(const bool submerged, CreaturePtr creature, const vector<BreatheType>& breathes) const
{
  int max_swimming_time = 0;

  if (creature != nullptr)
  {
    // Swimming below water - at this point we're basically checking to see how
    // long the creature can hold its breath.
    if (submerged)
    {
      max_swimming_time = creature->get_health().get_current() / HOLD_BREATH_HEALTH_DIVISOR;
    }
    // Above-water-swimming - checks the swimming skill
    else
    {
      max_swimming_time = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_SWIMMING) * MAXIMUM_SWIMMING_TIME_MULTIPLIER;
    }

    bool is_incorporeal = creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);
    bool can_breathe_water = creature->can_breathe(BreatheType::BREATHE_TYPE_WATER);

    // Spirits and water-breathers clearly can do this for a while.
    if (is_incorporeal || can_breathe_water)
    {
      max_swimming_time = std::numeric_limits<int>::max();
    }
  }

  return max_swimming_time;
}

// Swimming damage is always 10% of total HP.
int SwimmingCalculator::calculate_swimming_damage(CreaturePtr creature, const bool is_incorporeal) const
{
  int swimming_damage = 0;
  
  if (creature && !is_incorporeal)
  {
    Statistic hit_points = creature->get_hit_points();    
    swimming_damage = static_cast<int>(std::max(1.0f, static_cast<float>(hit_points.get_base()) * SWIMMING_DAMAGE_MAX_HP_MULTIPLIER));
  }
  
  return swimming_damage;
}
