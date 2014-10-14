#pragma once
#include <string>
#include "Creature.hpp"
#include "Deity.hpp"

class ReligionManager
{
  public:
    ReligionManager();

    DeityPtr get_deity(const std::string& deity_id) const;
    DeityPtr get_active_deity(CreaturePtr creature);
    DeityStatus get_active_deity_status(CreaturePtr creature);
    int get_piety_for_active_deity(CreaturePtr creature);
    std::string get_deity_name_sid(const std::string& deity_id) const;
    std::string get_death_message_sid(const std::string& deity_id) const;
};
