#include <boost/make_shared.hpp>
#include "StoneCalculator.hpp"
#include "StoneStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

StoneStatusEffect::StoneStatusEffect()
{
  status_calc = boost::make_shared<StoneCalculator>();
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

