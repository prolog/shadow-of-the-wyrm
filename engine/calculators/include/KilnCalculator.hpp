#pragma once
#include "Creature.hpp"

class KilnCalculator
{
  public:
    int calc_pct_chance_brand() const;

    int calc_min_free_enchants(CreaturePtr creature) const;
    int calc_max_free_enchants(CreaturePtr creature) const;

  protected:
    static const int ENCHANTS_CRAFTING_DIVISOR;
};

