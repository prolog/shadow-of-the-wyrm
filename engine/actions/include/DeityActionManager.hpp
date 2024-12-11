#pragma once
#include "Creature.hpp"
#include "Deity.hpp"
#include "Map.hpp"

// A class that gets informed of creature actions, and updates piety
// accordingly.
class DeityActionManager
{
  public:
    // Notify either a single deity (by default) or all deities of a
    // particular action.
    void notify_action(CreaturePtr creature, MapPtr map, const std::string& action_key, const bool active_deity_only = true, const uint num_times = 1);

  protected:
    void handle_displeasing_action(CreaturePtr creature, Deity* deity, const std::string& action_key, const uint num_times);
    void handle_pleasing_action(CreaturePtr creature, Deity* deity, const uint num_times);
    void add_displeasure_message(CreaturePtr creature, const std::string& displeasure_message_sid, const bool add_message_with_pause, const bool reload_map_music);
};

