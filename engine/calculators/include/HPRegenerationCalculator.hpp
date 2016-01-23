#pragma once
#include "common.hpp"
#include "Creature.hpp"

class HPRegenerationCalculator
{
  public:
    uint calculate_minutes_per_hp_tick(CreaturePtr creature, TilePtr tile);
    int calculate_hp_per_tick(CreaturePtr creature);

  protected:
    float get_hp_tick_health_multiplier(CreaturePtr creature);

    static const uint BASE_MINUTES_PER_HP_TICK;
    static const uint MIN_MINUTES_PER_HP_TICK;
};
