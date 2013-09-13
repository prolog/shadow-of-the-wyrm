#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "Map.hpp"

// The automatic movement coordinator determines whether to move
// automatically, and whether to disengage automatic movement after the
// action.
class AutomaticMovementCoordinator
{
  public:
    ActionCostValue auto_move(CreaturePtr creature, MapPtr map, const Direction d);

  protected:
    // Check to see if the creature can auto-move - no unsafe statuses like
    // extreme hunger.
    bool creature_can_auto_move(CreaturePtr creature);

    // Check to see if the map allows auto-movement - adjacent tile must be
    // safe, non-blocking, etc.
    bool tile_allows_auto_move(TilePtr tile);
};

