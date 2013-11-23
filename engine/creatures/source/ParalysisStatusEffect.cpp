#include "ParalysisCalculator.hpp"
#include "ParalysisStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

ParalysisStatusEffect::ParalysisStatusEffect()
{
  status_calc = std::make_shared<ParalysisCalculator>();
}

string ParalysisStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYZED);

  return message;
}

string ParalysisStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_paralyzed_message(creature);

  return message;
}

string ParalysisStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYSIS_CURED);
  
  return message;
}

string ParalysisStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_paralysis_message(creature);

  return message;
}

string ParalysisStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_PARALYSIS;
}
