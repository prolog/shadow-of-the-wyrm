#include "ActionTextKeys.hpp"
#include "SatedStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

SatedStatusEffect::SatedStatusEffect()
{
}

string SatedStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SATED);

  return message;
}

string SatedStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_sated_message(creature);

  return message;
}

string SatedStatusEffect::get_player_finalize_message() const
{
  return get_player_undo_message();
}

string SatedStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SATED_CURED);
  
  return message;
}

string SatedStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_sated_message(creature);

  return message;
}

string SatedStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_SATED;
}

