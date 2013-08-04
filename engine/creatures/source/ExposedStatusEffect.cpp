#include <boost/make_shared.hpp>
#include "ExposedCalculator.hpp"
#include "ExposedStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

ExposedStatusEffect::ExposedStatusEffect()
{
  status_calc = boost::make_shared<ExposedCalculator>();
}

string ExposedStatusEffect::get_player_application_message() const
{
  return StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_EXPOSED);
}

string ExposedStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  return StatusAilmentTextKeys::get_npc_exposed_message(creature);
}

string ExposedStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_EXPOSED_CURED);
  return message;
}

string ExposedStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_exposed_message(creature);

  return message;
}

string ExposedStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_EXPOSED;
}

