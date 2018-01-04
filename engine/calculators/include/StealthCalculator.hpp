#pragma once
#include "Creature.hpp"

class StealthCalculator
{
  public:
    int calculate_pct_chance_sneak_attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature) const;
};

