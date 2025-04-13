#include "CreatureTileSafetyChecker.hpp"
#include "CombatManager.hpp"
#include "DeathManagerFactory.hpp"
#include "DeathSourceTextKeys.hpp"
#include "Game.hpp"
#include "MovementAccumulationChecker.hpp"
#include "TerrainMovementAccumulationCheckerFactory.hpp"

using std::string;

void MovementAccumulationChecker::tick(CreaturePtr creature, TilePtr tile, const ulonglong /*minutes_this_tick*/, const ulonglong /*minutes_elapsed*/)
{
  if (creature)
  {
    CreatureTileSafetyChecker ctsc;
    MapPtr map = Game::instance().get_current_map();

    if (tile != nullptr && tile->get_unprotected_movement_is_death(creature) && !ctsc.is_tile_safe_for_creature(creature, tile))
    {
      CombatManager cm;
      int ripped_damage = creature->get_hit_points().get_current() + 1;
      Damage ripped_default;
      ripped_default.set_modifier(ripped_damage);
      string msg_sid;
      string death_source_sid = DeathSourceTextKeys::DEATH_SOURCE_DEATHLY_TILE;

      cm.deal_damage(nullptr, creature, AttackType::ATTACK_TYPE_MAGICAL, "", ripped_damage, ripped_default, msg_sid, death_source_sid);
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

