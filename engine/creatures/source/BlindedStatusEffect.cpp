#include <boost/make_shared.hpp>
#include "BlindedCalculator.hpp"
#include "BlindedStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

BlindedStatusEffect::BlindedStatusEffect()
{
  status_calc = boost::make_shared<BlindedCalculator>();
}

string BlindedStatusEffect::get_player_application_message() const
{
  return StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLINDED);
}

string BlindedStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  return StatusAilmentTextKeys::get_npc_blinded_message(creature);
}

string BlindedStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLINDNESS_CURED);
  return message;
}

string BlindedStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_blindness_message(creature);

  return message;
}

string BlindedStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_BLINDED;
}

