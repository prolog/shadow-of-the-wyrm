#pragma once
#include "common.hpp"
#include "Creature.hpp"

class HPRegenerationCalculator
{
  public:
    uint calculate_minutes_per_hit_point(CreaturePtr creature, TilePtr tile);

  protected:
    float get_health_multiplier(CreaturePtr creature);

    static const uint BASE_MINUTES_PER_HIT_POINT;
    static const uint MIN_MINUTES_PER_HIT_POINT;
};
