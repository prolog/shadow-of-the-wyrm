#pragma once
#include "Creature.hpp"

class ExperienceManager
{
  public:
    ExperienceManager();
    ~ExperienceManager();

    uint get_current_experience_needed_for_level(CreaturePtr creature, const uint level);
    bool gain_experience(CreaturePtr creature, const uint experience_value);
    uint get_pct_to_next_level(CreaturePtr creature);
    
    void run_level_script(CreaturePtr creature);

protected:
    bool can_gain_level(CreaturePtr creature);

    uint get_total_experience_needed_for_lvl_idx(CreaturePtr creature, const uint level_idx);

    void level_up(CreaturePtr creature);
    void gain_level(CreaturePtr creature);
    void gain_hp_and_ap(CreaturePtr creature);
    void gain_statistics_if_necessary(CreaturePtr creature);
    
    // The actual experience table
    static const uint base_experience_table[];
    static const int base_experience_table_size;
};
