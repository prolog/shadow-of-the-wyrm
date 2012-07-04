#pragma once
#include "Creature.hpp"
#include "MovementTypes.hpp"
#include "Tile.hpp"

class MovementAccumulationUpdater
{
  public:
    void update(CreaturePtr creature, TilePtr new_tile);

  protected:
    MovementType get_movement_type(CreaturePtr creature, TilePtr tile);
};
