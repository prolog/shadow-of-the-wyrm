#include "MutenessCalculator.hpp"
#include "MutenessStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

MutenessStatusEffect::MutenessStatusEffect()
{
  status_calc = std::make_shared<MutenessCalculator>();
}

string MutenessStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTED);
  return message;
}

string MutenessStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_muted_message(creature);

  return message;
}

string MutenessStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTENESS_CURED);
  return message;
}

string MutenessStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_muteness_message(creature);

  return message;
}

string MutenessStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_MUTE;
}