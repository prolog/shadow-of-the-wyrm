#include <boost/make_shared.hpp>
#include "ParalysisCalculator.hpp"
#include "ParalysisStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

ParalysisStatusEffect::ParalysisStatusEffect()
{
  status_calc = boost::make_shared<ParalysisCalculator>();
}

string ParalysisStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYZED);

  return message;
}

string ParalysisStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYSIS_CURED);
  
  return message;
}

string ParalysisStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_PARALYSIS;
}
