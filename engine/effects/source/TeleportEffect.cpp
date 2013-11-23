#include "AdditionalEffectMessages.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "RNG.hpp"
#include "TeleportEffect.hpp"

using std::string;

TeleportEffect::TeleportEffect()
{
}

string TeleportEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
    effect_msg = EffectTextKeys::get_teleport_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

Effect* TeleportEffect::clone()
{
  return new TeleportEffect(*this);
}

bool TeleportEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return teleport(creature);
}

bool TeleportEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return teleport(creature);
}

bool TeleportEffect::effect_cursed(CreaturePtr creature, ActionManager * am)
{
  return teleport(creature);
}

bool TeleportEffect::teleport(CreaturePtr creature)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  // The creature's original tile.
  TilePtr old_tile = map->at(map->get_location(creature->get_id()));

  bool teleported = false;

  // Make a number of attempts to teleport.
  for (int i = 0; i < 100; i++)
  {
    int row = RNG::range(0, rows);
    int col = RNG::range(0, cols);

    Coordinate c(row, col);
    TilePtr tile = map->at(c);

    if (tile && !tile->get_creature() && !tile->get_is_blocking(creature))
    {
      MapUtils::add_or_update_location(map, creature, c, old_tile);
      teleported = true;

      // Originally, I didn't have the break statement below.
      // End result?  Lots of player shared_ptrs all over the map!
      // Hilarity ensues!
      break;
    }
  }

  return teleported;
}