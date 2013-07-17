#include "CurrentCreatureAbilities.hpp"
#include "MessageManager.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Check to see if the creature can speak (is not muted).
bool CurrentCreatureAbilities::can_speak(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak) const
{
  bool creature_can_speak = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_MUTE) == false);

  if (add_message_if_player_and_cannot_speak && !creature_can_speak && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTED);
  }

  return creature_can_speak;
}

// Check to see if the creature can act (is not paralyzed)
bool CurrentCreatureAbilities::can_act(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak) const
{
  bool creature_can_act = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_PARALYSIS) == false);

  if (add_message_if_player_and_cannot_speak && !creature_can_act && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYZED);
  }

  return creature_can_act;
}

void CurrentCreatureAbilities::add_ability_message_for_sid(const string& status_ability_message_sid) const
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(status_ability_message_sid));
  manager.send();
}
