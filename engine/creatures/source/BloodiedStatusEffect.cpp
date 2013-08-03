#include <boost/make_shared.hpp>
#include "BloodiedCalculator.hpp"
#include "BloodiedStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

const int BloodiedStatusEffect::BLOODIED_TO_HIT_PENALTY = -15;

BloodiedStatusEffect::BloodiedStatusEffect()
{
  status_calc = boost::make_shared<BloodiedCalculator>();
}

string BloodiedStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED);
  return message;
}

string BloodiedStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_bloodied_message(creature);

  return message;
}

string BloodiedStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED_CURED);
  return message;
}

string BloodiedStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_bloodied_message(creature);

  return message;
}

int BloodiedStatusEffect::get_to_hit_bonus(CreaturePtr creature) const
{
  return BLOODIED_TO_HIT_PENALTY;
}

string BloodiedStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_BLOODIED;
}
