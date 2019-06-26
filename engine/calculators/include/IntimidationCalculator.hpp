#pragma once
#include "Creature.hpp"

class IntimidationCalculator
{
  public:
    int calculate_pct_chance_intimidated(CreaturePtr attacking_creature, CreaturePtr attacked_creature);

  protected:
    static const int MAX_PCT_CHANCE_INTIMIDATION;
    static const int INTIMIDATION_DIVISOR;
    static const int CHARISMA_DIVISOR;
    static const int LEVEL_DIVISOR;
};
