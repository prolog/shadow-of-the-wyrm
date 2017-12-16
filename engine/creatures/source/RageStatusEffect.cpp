#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "RageCalculator.hpp"
#include "RageStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

RageStatusEffect::RageStatusEffect()
{
  status_calc = std::make_shared<RageCalculator>();
}

bool RageStatusEffect::is_negative() const
{
  return false;
}

string RageStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_RAGE);
  return message;
}

string RageStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_rage_message(creature);
  return message;
}

string RageStatusEffect::get_player_finalize_message() const
{
  return get_player_undo_message();
}

string RageStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_RAGE_CURED);
  return message;
}

string RageStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_rage_message(creature);
  return message;
}

string RageStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_RAGE;
}

