#pragma once
#include "Creature.hpp"

// A class for checking if the creature has particular capabilities, and
// potentially adding a message if not.
class CurrentCreatureAbilities
{
  public:
    bool can_speak(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak = false) const;
    bool can_move(CreaturePtr creature, const bool add_message_if_player_and_cannot_move = false) const;
    bool can_see(CreaturePtr creature, const bool add_message_if_player_and_cannot_see = false) const;
    bool can_hear(CreaturePtr creature, const bool add_message_if_player_and_cannot_hear = false) const;
    bool can_read(CreaturePtr creature, const bool add_message_if_player_and_cannot_read = false) const;

    // can_select_movement_direction is used to determine if the creature can
    // select a movement direction - stunned creatures can try to move, but
    // there is a good chance that they will not get the intended direction.
    bool can_select_movement_direction(CreaturePtr creature, const bool add_message_if_player_and_cannot_move = false) const;

    // can_act is very general - it asks if the creature can perform any action
    // at all.  The only case when a creature can't should be when the creature
    // is paralyzed.
    bool can_act(CreaturePtr creature, const bool add_message_if_player_and_cannot_act = false) const;

  protected:
    void add_ability_message_for_sid(CreaturePtr creature, const std::string& ability_message) const;
};

