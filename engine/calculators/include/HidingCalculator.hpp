#pragma once
#include "Creature.hpp"
#include "Map.hpp"

class HidingCalculator
{
  public:
    int calculate_pct_chance_hide(CreaturePtr creature, MapPtr map) const;
};

