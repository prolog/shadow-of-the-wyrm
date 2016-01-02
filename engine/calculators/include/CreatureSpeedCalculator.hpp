#pragma once
#include "Creature.hpp"

class CreatureSpeedCalculator
{
  public:
    int calculate(CreaturePtr creature) const;

  protected:
    int get_equipment_bonus(CreaturePtr creature) const;
    float get_multiplier(CreaturePtr creature) const;

    const static float BURDENED_SPEED_MULTIPLIER;
    const static float STRAINED_SPEED_MULTIPLIER;
};

