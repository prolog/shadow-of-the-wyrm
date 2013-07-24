#include <boost/make_shared.hpp>
#include "CombatManager.hpp"
#include "StoneCalculator.hpp"
#include "StoneStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

StoneStatusEffect::StoneStatusEffect()
{
  status_calc = boost::make_shared<StoneCalculator>();
}

void StoneStatusEffect::finalize(CreaturePtr creature) const
{
  CombatManager cm;
  CreaturePtr no_creature;
  string message_sid = StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE_FINALIZE;

  cm.deal_damage(no_creature, creature, creature->get_hit_points().get_base(), message_sid);
}

string StoneStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE);
  
  return message;
}

string StoneStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE_CURED);
  
  return message;
}

string StoneStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_STONE;
}

