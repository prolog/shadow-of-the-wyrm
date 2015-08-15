#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "TimewalkCalculator.hpp"
#include "TimewalkStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

TimewalkStatusEffect::TimewalkStatusEffect()
{
  status_calc = std::make_shared<TimewalkCalculator>();
}

string TimewalkStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_TIMEWALK);

  return message;
}

string TimewalkStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_timewalk_message(creature);

  return message;
}

string TimewalkStatusEffect::get_player_finalize_message() const
{
  return get_player_undo_message();
}

string TimewalkStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_TIMEWALK_CURED);
  
  return message;
}

string TimewalkStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_timewalk_message(creature);

  return message;
}

string TimewalkStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_TIMEWALK;
}

