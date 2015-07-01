#pragma once
#include "Creature.hpp"

class CreatureSpeedCalculator
{
  public:
    int calculate(CreaturePtr creature) const;

  protected:
    const static float BURDENED_SPEED_MULTIPLIER;
    const static float STRAINED_SPEED_MULTIPLIER;
};

