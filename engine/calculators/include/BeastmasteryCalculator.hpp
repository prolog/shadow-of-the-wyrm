#pragma once
#include "Creature.hpp"

class BeastmasteryCalculator
{
  public:
    int calculate_pct_chance_tame(CreaturePtr taming_creature, CreaturePtr tamed_creature);
    double calculate_exp_proportion(CreaturePtr taming_creature);

  protected:
    static const int MAX_PCT_CHANCE_TAME;
};
