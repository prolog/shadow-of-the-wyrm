#pragma once
#include "Creature.hpp"

class CreaturePietyCalculator
{
  public:
    // When gaining piety gain/loss, use the multiplier (either to
    // multiply, for piety gain, or to divide, for piety loss).
    float calculate_piety_multiplier(CreaturePtr creature);

    // Calculates the per-tick piety regen bonus based on the creature's
    // class and deity relations.
    int calculate_piety_regen_bonus(CreaturePtr creature);
};

