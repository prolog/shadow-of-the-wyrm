#pragma once
#include "common.hpp"
#include "Creature.hpp"

class HPRegenerationCalculator
{
  public:
    uint calculate_minutes_per_hit_point(CreaturePtr creature);
};
