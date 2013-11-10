#include <boost/make_shared.hpp>
#include "Creature.hpp"
#include "IncorporealCalculator.hpp"
#include "IncorporealStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

IncorporealStatusEffect::IncorporealStatusEffect()
{
  status_calc = boost::make_shared<IncorporealCalculator>();
}

string IncorporealStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_INCORPOREAL);

  return message;
}

string IncorporealStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_hasted_message(creature);

  return message;
}

string IncorporealStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_INCORPOREAL_CURED);
  
  return message;
}

string IncorporealStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_incorporeal_message(creature);

  return message;
}

string IncorporealStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_INCORPOREAL;
}

