#include <boost/make_shared.hpp>
#include "BlindedCalculator.hpp"
#include "BlindedStatusEffect.hpp"
#include "Game.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

const int BlindedStatusEffect::BLINDED_TO_HIT_PENALTY = -10;
const int BlindedStatusEffect::BLINDED_EVADE_PENALTY = -10;

BlindedStatusEffect::BlindedStatusEffect()
{
  status_calc = boost::make_shared<BlindedCalculator>();
}

int BlindedStatusEffect::get_to_hit_bonus(CreaturePtr creature) const
{
  return BLINDED_TO_HIT_PENALTY;
}

int BlindedStatusEffect::get_evade_bonus(CreaturePtr creature) const
{
  return BLINDED_EVADE_PENALTY;
}

bool BlindedStatusEffect::after_apply(CreaturePtr creature) const
{
  Game::instance().get_loaded_map_details_ref().update_blind_status(true);
  return true;
}

void BlindedStatusEffect::after_undo(CreaturePtr creature) const
{
  Game::instance().get_loaded_map_details_ref().update_blind_status(false);
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

