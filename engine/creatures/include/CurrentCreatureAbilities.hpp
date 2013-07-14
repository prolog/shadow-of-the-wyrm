#pragma once
#include "Creature.hpp"

// A class for checking if the creature has particular capabilities, and
// potentially adding a message if not.
class CurrentCreatureAbilities
{
  public:
    bool can_speak(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak = false) const;

  protected:
    void add_ability_message_for_sid(const std::string& ability_message) const;
};

