#pragma once
#include "Creature.hpp"

class BrewingCalculator
{
  public:
    int calc_pct_chance_additional_potion(CreaturePtr brewing_creature) const;

  protected:
    static const int ADDITIONAL_POTION_BREWING_DIVISOR;
};

