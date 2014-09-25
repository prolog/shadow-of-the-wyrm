#pragma once
#include "Creature.hpp"

// A class that gets informed of creature actions, and updates piety
// accordingly.
class DeityActionManager
{
  public:
    // Notify either a single deity (by default) or all deities of a
    // particular action.
    void notify_action(CreaturePtr creature, const std::string& action_key, const bool active_deity_only = true);

  protected:
    void handle_displeasing_action(CreaturePtr creature);
    void add_displeasure_message(CreaturePtr creature, const std::string& displeasure_message_sid);
};

