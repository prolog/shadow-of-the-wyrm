#pragma once
#include "Creature.hpp"

class ForagablesCalculator
{
  public:
    int calculate_pct_chance_foragables(CreaturePtr creature);
    int calculate_pct_chance_herbs(CreaturePtr creature);
};
