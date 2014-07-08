#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "FlyingCalculator.hpp"
#include "FlyingStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

FlyingStatusEffect::FlyingStatusEffect()
{
  status_calc = std::make_shared<FlyingCalculator>();
}

string FlyingStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_FLYING);

  return message;
}

string FlyingStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_flying_message(creature);

  return message;
}

string FlyingStatusEffect::get_player_finalize_message() const
{
  return get_player_undo_message();
}

string FlyingStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_FLYING_CURED);
  
  return message;
}

string FlyingStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_flying_message(creature);

  return message;
}

string FlyingStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_FLYING;
}

