#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "Game.hpp"
#include "FlyingCalculator.hpp"
#include "FlyingStatusEffect.hpp"
#include "TerrainMovementAccumulationCheckerFactory.hpp"
#include "MapUtils.hpp"
#include "MovementAccumulationUpdater.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

FlyingStatusEffect::FlyingStatusEffect()
{
  status_calc = std::make_shared<FlyingCalculator>();
}

string FlyingStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_FLYING);

  return message;
}

string FlyingStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_flying_message(creature);

  return message;
}

string FlyingStatusEffect::get_player_finalize_message() const
{
  return get_player_undo_message();
}

void FlyingStatusEffect::after_finalize(CreaturePtr creature) const
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    // JCD FIXME: Add this for Incorporeal, too!  Create FloatingStatusEffect that just
    // implements this function - Flying and Incorporeal should inherit from it.
    //
    // Recheck the terrain movement accumulator now that the creature is no longer flying.
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

string FlyingStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_FLYING_CURED);
  
  return message;
}

string FlyingStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_flying_message(creature);

  return message;
}

string FlyingStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_FLYING;
}

