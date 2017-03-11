#pragma once
#include "Creature.hpp"

class SwimmingCalculator
{
  public:
    int calculate_maximum_swimming_time(const bool submerged, CreaturePtr creature, const std::vector<BreatheType>& breathes) const;
    int calculate_swimming_damage(CreaturePtr creature, const bool is_incorporeal) const;

  protected:
    bool is_incorporeal;
    
    static const int MAXIMUM_SWIMMING_TIME_MULTIPLIER;
    static const float SWIMMING_DAMAGE_MAX_HP_MULTIPLIER;
    static const int HOLD_BREATH_HEALTH_DIVISOR;
};
