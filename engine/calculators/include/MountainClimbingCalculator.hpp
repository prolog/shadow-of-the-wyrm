#pragma once
#include "Creature.hpp"

class MountainClimbingCalculator
{
  public:
    int calculate_max_mountain_climbing_time(const int mountain_lore_skill_value, const bool is_incorporeal) const;
    bool generate_does_fall_from_exhaustion(const int mountain_lore_skill_value, const bool is_incorporeal) const;
    int generate_falling_damage(CreaturePtr creature) const;

  protected:
    static const int MAXIMUM_CLIMBING_TIME_MULTIPLIER;
    // The chance of falling, applied each tick by multiplying by the mountain lore skill.
    static const int FALLING_CHANCE_MULTIPLIER;
    static const int PCT_CHANCE_PERCENTAGE_DAMAGE;
};
