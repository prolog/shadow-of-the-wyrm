#pragma once
#include "Creature.hpp"

class HostilityManager
{
  public:
    void set_hostility_to_creature(CreaturePtr creature, const std::string& hostile_to_creature_id);
    void set_hostility_to_player(CreaturePtr creature, const bool hostility = true);
};

