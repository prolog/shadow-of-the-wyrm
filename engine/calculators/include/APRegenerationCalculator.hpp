#pragma once
#include "common.hpp"
#include "Creature.hpp"

class APRegenerationCalculator
{
  public:
    uint calculate_minutes_per_arcana_point(CreaturePtr creature, TilePtr tile);

  protected:
    static const uint BASE_MINUTES_PER_ARCANA_POINT;
};
