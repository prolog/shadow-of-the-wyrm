#pragma once
#include "ICreatureRegeneration.hpp"
#include "common.hpp"
#include "Creature.hpp"
#include "Tile.hpp"

// Accumulates time on the existing movement accumulation values for the creature.
// Does not actually handle changing the values (e.g., on changing tiles, having
// no more boats due to dropping, etc.)
class MovementAccumulator : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;
};
