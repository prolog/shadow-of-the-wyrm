#pragma once
#include "Creature.hpp"

class CorpseCalculator
{
  public:
    int calculate_chance_successful_skin(CreaturePtr creature);
    int calculate_chance_resistance(CreaturePtr creature);
    int calculate_chance_corpse(CreaturePtr deathblow_creature);
    int calculate_chance_primordial_essence(CreaturePtr attacking_creature, CreaturePtr deathblow_creature);

  protected:
    static const int BASE_CHANCE_PRIMORDIAL_ESSENCE;
    static const int PRIMORDIAL_ESSENCE_SKILL_DIVISOR;
};

