#pragma once
#include "Creature.hpp"

class CreaturePietyCalculator
{
  public:
    // When gaining piety gain/loss, use the multiplier (either to
    // multiply, for piety gain, or to divide, for piety loss).
    float calculate_piety_multiplier(CreaturePtr creature);
};

