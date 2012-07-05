#include "MovementAccumulationChecker.hpp"
#include "TerrainMovementAccumulationCheckerFactory.hpp"

void MovementAccumulationChecker::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong minutes_elapsed)
{
  if (creature)
  {
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    ITerrainMovementAccumulationCheckerPtr checker = TerrainMovementAccumulationCheckerFactory::create_terrain_movement_accumulation_checker(movement_accumulation);
  }
}
