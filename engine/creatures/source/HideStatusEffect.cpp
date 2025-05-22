#include "ActionTextKeys.hpp"
#include "Creature.hpp"
#include "CreatureProperties.hpp"
#include "HideStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"
#include "UntimedStatusCalculator.hpp"

using namespace std;

HideStatusEffect::HideStatusEffect()
{
  status_calc = std::make_shared<UntimedStatusCalculator>();
}

bool HideStatusEffect::is_negative() const
{
  return false;
}

bool HideStatusEffect::after_apply(CreaturePtr creature) const
{
  bool applied = false;

  if (creature != nullptr)
  {
    creature->set_free_hidden_actions(2);
    applied = true;
  }

  return applied;
}

void HideStatusEffect::after_finalize(CreaturePtr creature) const
{
  // Once a creature is revealed, they cannot hide again the next turn.
  if (creature != nullptr)
  {
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_HIDING_COOLDOWN, std::to_string(true));
  }
}

string HideStatusEffect::get_player_application_message() const
{
  string no_message;
  return no_message;
}

string HideStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_hide_message(creature);
  return message;
}

string HideStatusEffect::get_player_finalize_message() const
{
  return get_player_undo_message();
}

string HideStatusEffect::get_player_undo_message() const
{
  string no_message;
  return no_message;
}

string HideStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_hide_reveal_message(creature);
  return message;
}

string HideStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_HIDE;
}

