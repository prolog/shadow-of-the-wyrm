#include "CurrentCreatureAbilities.hpp"
#include "MessageManagerFactory.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Check to see if the creature can speak (is not muted).
bool CurrentCreatureAbilities::can_speak(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak) const
{
  bool creature_can_speak = creature && can_act(creature) && (creature->has_status(StatusIdentifiers::STATUS_ID_MUTE) == false);

  if (add_message_if_player_and_cannot_speak && !creature_can_speak && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTED);
  }

  return creature_can_speak;
}

// Check to see if the creature can see (has not been blinded).
bool CurrentCreatureAbilities::can_see(CreaturePtr creature, const bool add_message_if_player_and_cannot_see) const
{
  bool creature_can_see = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_BLINDED) == false);

  if (add_message_if_player_and_cannot_see && !creature_can_see && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLINDED);
  }

  return creature_can_see;
}

bool CurrentCreatureAbilities::can_hear(CreaturePtr creature, const bool add_message_if_player_and_cannot_hear) const
{
  bool creature_can_hear = creature;

  return creature_can_hear;
}

// Check to see if the creature can move (is not spellbound)
bool CurrentCreatureAbilities::can_move(CreaturePtr creature, const bool add_message_if_player_and_cannot_move) const
{
  bool creature_can_move = creature && can_act(creature) && (creature->has_status(StatusIdentifiers::STATUS_ID_SPELLBOUND) == false);

  if (add_message_if_player_and_cannot_move && !creature_can_move && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SPELLBOUND);
  }

  return creature_can_move;
}

// Check to see if the creature can act (is not paralyzed)
bool CurrentCreatureAbilities::can_act(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak) const
{
  bool creature_can_act = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_PARALYSIS) == false);

  if (add_message_if_player_and_cannot_speak && !creature_can_act && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYZED);
  }

  return creature_can_act;
}

// Check to see if the creature can select their movement direction -
// false if the creature is stunned.
bool CurrentCreatureAbilities::can_select_movement_direction(CreaturePtr creature, const bool add_message_if_player_and_stunned) const
{
  bool creature_can_select = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_STUNNED) == false);

  if (add_message_if_player_and_stunned && !creature_can_select && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STUNNED);
  }

  return creature_can_select;
}

void CurrentCreatureAbilities::add_ability_message_for_sid(CreaturePtr creature, const string& status_ability_message_sid) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);

  manager.add_new_message(StringTable::get(status_ability_message_sid));
  manager.send();
}
