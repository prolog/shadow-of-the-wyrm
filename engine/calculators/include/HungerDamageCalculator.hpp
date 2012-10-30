#pragma once
#include "Creature.hpp"

class HungerDamageCalculator
{
  public:
    int calculate_hunger_damage(CreaturePtr creature, const ulonglong num_ticks) const;

  protected:
    static const int HUNGER_DAMAGE_PER_TICK;
};

