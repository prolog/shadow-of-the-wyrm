#pragma once
#include "Creature.hpp"

class CorpseCalculator
{
  public:
    int calculate_chance_successful_skin(CreaturePtr creature);
    int calculate_chance_resistance(CreaturePtr creature);
    int calculate_chance_corpse(CreaturePtr deathblow_creature);
};

