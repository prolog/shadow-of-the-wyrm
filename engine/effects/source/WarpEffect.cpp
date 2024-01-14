#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapTypes.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "WarpEffect.hpp"

using namespace std;

string WarpEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
    effect_msg = EffectTextKeys::get_warp_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

Effect* WarpEffect::clone()
{
  return new WarpEffect(*this);
}

bool WarpEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return warp(creature);
}

bool WarpEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return warp(creature);
}

bool WarpEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return warp(creature);
}

bool WarpEffect::warp(CreaturePtr creature)
{
  bool warped = false;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    MapPtr old_map = game.get_current_map();

    if (old_map && old_map->get_map_id() != MapID::MAP_ID_WORLD_MAP)
    {
      MapPtr new_map = game.get_map_registry_ref().get_map(MapID::MAP_ID_WORLD_MAP);
      TilePtr creature_tile = MapUtils::get_tile_for_creature(old_map, creature);
      Game::instance().get_sound()->play(SoundEffectID::TELEPORT);
      GameUtils::move_to_new_map(creature_tile, old_map, new_map);

      warped = true;
    }
  }

  return warped;
}

