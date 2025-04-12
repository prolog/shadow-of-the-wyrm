#include "CreatureTileSafetyChecker.hpp"
#include "DeathManagerFactory.hpp"
#include "Game.hpp"
#include "MovementAccumulationChecker.hpp"
#include "TerrainMovementAccumulationCheckerFactory.hpp"

void MovementAccumulationChecker::tick(CreaturePtr creature, TilePtr tile, const ulonglong /*minutes_this_tick*/, const ulonglong /*minutes_elapsed*/)
{
  if (creature)
  {
    CreatureTileSafetyChecker ctsc;
    MapPtr map = Game::instance().get_current_map();

    if (tile != nullptr && tile->get_unprotected_movement_is_death(creature) && !ctsc.is_tile_safe_for_creature(creature, tile))
    {
      // TODO add message
      DeathManagerPtr death_manager = DeathManagerFactory::create_death_manager(nullptr, creature, map);
      death_manager->die();
      return;
    }

    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    ITerrainMovementAccumulationCheckerPtr checker = TerrainMovementAccumulationCheckerFactory::create_terrain_movement_accumulation_checker(movement_accumulation);
    
    if (checker)
    {
      checker->check(creature);
    }
  }
}

