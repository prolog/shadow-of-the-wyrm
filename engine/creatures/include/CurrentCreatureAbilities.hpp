#pragma once
#include "Creature.hpp"

// A class for checking if the creature has particular capabilities, and
// potentially adding a message if not.
class CurrentCreatureAbilities
{
  public:
    bool can_speak(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak = false) const;
    bool can_move(CreaturePtr creature, const bool add_message_if_player_and_cannot_move = false) const;

    // can_act is very general - it asks if the creature can perform any action
    // at all.  The only case when a creature can't should be when the creature
    // is paralyzed.
    bool can_act(CreaturePtr creature, const bool add_message_if_player_and_cannot_act = false) const;

  protected:
    void add_ability_message_for_sid(CreaturePtr creature, const std::string& ability_message) const;
};

