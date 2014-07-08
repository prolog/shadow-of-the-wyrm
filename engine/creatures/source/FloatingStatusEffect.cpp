#include "Game.hpp"
#include "FloatingStatusEffect.hpp"
#include "MapUtils.hpp"
#include "MovementAccumulationUpdater.hpp"
#include "TerrainMovementAccumulationCheckerFactory.hpp"

void FloatingStatusEffect::after_undo(CreaturePtr creature) const
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    // Recheck the terrain movement accumulator now that the creature is no longer floating.
    // It's possible that the player is about to learn a hard lesson about simulated
    // gravity.
    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

    MovementAccumulationUpdater mau;
    mau.update(creature, tile);

    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    ITerrainMovementAccumulationCheckerPtr checker = TerrainMovementAccumulationCheckerFactory::create_terrain_movement_accumulation_checker(movement_accumulation);

    if (checker)
    {
      checker->check(creature);
    }
  }
}

