#include <boost/make_shared.hpp>
#include "DisfiguredCalculator.hpp"
#include "DisfiguredStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

DisfiguredStatusEffect::DisfiguredStatusEffect()
{
  status_calc = boost::make_shared<DisfiguredCalculator>();
}

string DisfiguredStatusEffect::get_player_application_message() const
{
  return StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DISFIGURED);
}

string DisfiguredStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  return StatusAilmentTextKeys::get_npc_disfigured_message(creature);
}

string DisfiguredStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DISFIGURED_CURED);
  return message;
}

string DisfiguredStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_disfigured_message(creature);

  return message;
}

string DisfiguredStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_DISFIGURED;
}
