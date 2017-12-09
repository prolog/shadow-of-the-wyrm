#pragma once
#include "Creature.hpp"
#include "ThreatConstants.hpp"

class HostilityManager
{
  public:
    void set_hostility_to_creature(CreaturePtr creature, const std::string& hostile_to_creature_id, const int hostility_level = ThreatConstants::INITIAL_THREAT_RATING);
    void set_hostility_to_player(CreaturePtr creature, const bool hostility = true, const int hostility_level = ThreatConstants::INITIAL_THREAT_RATING);
    void remove_hostility_to_creature(CreaturePtr creature, const std::string& hostile_to_creature_id);
};

