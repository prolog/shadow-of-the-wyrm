#pragma once
#include "Creature.hpp"

class SwimmingCalculator
{
  public:
    int calculate_maximum_swimming_time(const int swimming_skill_value) const;
    int calculate_swimming_damage(CreaturePtr creature) const;

  protected:
    static const int MAXIMUM_SWIMMING_TIME_MULTIPLIER;
    static const float SWIMMING_DAMAGE_MAX_HP_MULTIPLIER;
};
