#pragma once
#include "Creature.hpp"

// A class that gets informed of creature actions, and updates piety
// accordingly.
class DeityActionManager
{
  public:
    void notify_action(CreaturePtr creature, const std::string& action_key);

  protected:
    void handle_displeasing_action(CreaturePtr creature);
    void add_displeasure_message(CreaturePtr creature, const std::string& displeasure_message_sid);
};

