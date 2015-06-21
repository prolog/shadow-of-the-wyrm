#pragma once
#include "Creature.hpp"
#include "ICreatureRegeneration.hpp"

// Checks things like swimming, mountain climbing, etc., that are based off
// the movement accumulation mechanism and player skills.
class MovementAccumulationChecker : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong minutes_elapsed) override;
};
