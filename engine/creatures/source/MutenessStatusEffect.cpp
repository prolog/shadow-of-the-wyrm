#include <boost/make_shared.hpp>
#include "MutenessCalculator.hpp"
#include "MutenessStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

MutenessStatusEffect::MutenessStatusEffect()
{
  status_calc = boost::make_shared<MutenessCalculator>();
}

string MutenessStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTED);
  return message;
}

string MutenessStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTENESS_CURED);
  return message;
}

string MutenessStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_MUTE;
}