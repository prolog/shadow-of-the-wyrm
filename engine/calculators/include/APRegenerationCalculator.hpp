#pragma once
#include "common.hpp"
#include "Creature.hpp"

class APRegenerationCalculator
{
  public:
    uint calculate_minutes_per_ap_tick(CreaturePtr creature, TilePtr tile);
    int calculate_ap_per_tick(CreaturePtr creature);

  protected:
    float get_ap_tick_willpower_multiplier(CreaturePtr creature);

    static const uint BASE_MINUTES_PER_AP_TICK;
    static const uint MIN_MINUTES_PER_AP_TICK;
};
