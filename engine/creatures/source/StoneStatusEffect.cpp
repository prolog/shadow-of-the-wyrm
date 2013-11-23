#include "CombatManager.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "StoneCalculator.hpp"
#include "StoneStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatueGenerator.hpp"
#include "StatusTypes.hpp"

using namespace std;

StoneStatusEffect::StoneStatusEffect()
{
  status_calc = std::make_shared<StoneCalculator>();
}

void StoneStatusEffect::finalize(CreaturePtr creature) const
{
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  CombatManager cm;
  CreaturePtr no_creature;
  string message_sid = StatusAilmentTextKeys::STATUS_MESSAGE_STONE_FINALIZE;
 
  cm.deal_damage(no_creature, creature, creature->get_hit_points().get_base());

  TilePtr creature_tile = MapUtils::get_tile_for_creature(current_map, creature);

  // Ensure that the tile doesn't already have a feature.
  if (creature_tile && !creature_tile->has_feature())
  {
    // Get the description so the statue can be "a statue of a goblin", etc.
    string description_sid = creature->get_description_sid();

    // Generate the statue
    PetrifiedCorpseStatuePtr corpse_statue = StatueGenerator::generate_petrified_corpse_statue(description_sid);

    // Add it to the tile
    creature_tile->set_feature(corpse_statue);
  }
  else
  {
    // Because each tile can only have one feature, add a message about the statue
    // immediately crumbling into dust.
    message_sid = StatusAilmentTextKeys::STATUS_MESSAGE_STONE_CRUMBLE;
  }

  manager.add_new_message(StringTable::get(message_sid));
  manager.send();
}

string StoneStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE);
  
  return message;
}

string StoneStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_stone_message(creature);
  return message;
}

string StoneStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE_CURED);
  
  return message;
}

string StoneStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_stone_message(creature);
  return message;
}

string StoneStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_STONE;
}

