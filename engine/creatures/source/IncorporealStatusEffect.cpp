#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "Game.hpp"
#include "IncorporealCalculator.hpp"
#include "IncorporealStatusEffect.hpp"
#include "MapUtils.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

IncorporealStatusEffect::IncorporealStatusEffect()
{
  status_calc = std::make_shared<IncorporealCalculator>();
}

void IncorporealStatusEffect::after_undo(CreaturePtr creature) const
{
  // First, check the parent class to make sure that floating down
  // hasn't become suddenly dangerous...
  FloatingStatusEffect::after_undo(creature);

  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

  if (tile)
  {
    // Check to see if the tile is inaccessible, and double-check that
    // the creature no longer is incorporeal.  If both of these are
    // true, the creature has entered into a "blocked" tile and then
    // come out of wraith form/etc, and is instantly killed.
    if (tile->get_is_blocking(creature) && !creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL))
    {
      CombatManager cm;
      CreaturePtr no_attacker;
      string torn_apart_message_sid = ActionTextKeys::ACTION_PLAYER_OBLITERATED;

      cm.deal_damage(no_attacker, creature, creature->get_hit_points().get_current() + 1, torn_apart_message_sid);
    }
  }
}

string IncorporealStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_INCORPOREAL);

  return message;
}

string IncorporealStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_incorporeal_message(creature);

  return message;
}

string IncorporealStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_INCORPOREAL_CURED);
  
  return message;
}

string IncorporealStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_incorporeal_message(creature);

  return message;
}

string IncorporealStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_INCORPOREAL;
}

