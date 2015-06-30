#include "SpellboundCalculator.hpp"
#include "SpellboundStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

SpellboundStatusEffect::SpellboundStatusEffect()
{
  status_calc = std::make_shared<SpellboundCalculator>();
}

string SpellboundStatusEffect::get_player_application_message() const
{
  return StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_IMMOBILE);
}

string SpellboundStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  return StatusAilmentTextKeys::get_npc_immobile_message(creature);
}

string SpellboundStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_IMMOBILE_CURED);
  return message;
}

string SpellboundStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_immobile_message(creature);

  return message;
}

string SpellboundStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_SPELLBOUND;
}

