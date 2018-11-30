#pragma once
#include "Creature.hpp"

class PapercraftCalculator
{
  public:
    int calculate_pct_chance_success(CreaturePtr creature);

  protected:
    static const int BASE_PCT_CHANCE_SUCCESS;
    static const int PAPERCRAFT_SKILL_DIVISOR;
};

