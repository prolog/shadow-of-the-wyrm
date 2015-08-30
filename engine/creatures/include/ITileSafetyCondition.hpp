#pragma once
#include "Creature.hpp"
#include "Tile.hpp"

// Interface for tile safety checks.  Implementations provide a specific
// check: for lava, for water-type tiles, etc.  The NPC pathfinding
// algorithms use these safety conditions to determine whether or not to
// include a particular tile in the search algorithm.
class ITileSafetyCondition
{
  public:
    virtual bool is_safe(CreaturePtr creature, TilePtr tile) = 0;
};

using ITileSafetyConditionPtr = std::shared_ptr<ITileSafetyCondition>;

