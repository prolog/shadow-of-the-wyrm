#pragma once
#include "Creature.hpp"

class ThieveryCalculator
{
  public:
    int calculate_pct_chance_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature);
};

