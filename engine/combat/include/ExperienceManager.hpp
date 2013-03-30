#pragma once
#include "Creature.hpp"

class ExperienceManager
{
  public:
    ExperienceManager();
    ~ExperienceManager();

    bool gain_experience(CreaturePtr creature, const uint experience_value);
    uint get_pct_to_next_level(CreaturePtr creature);
    
  protected:
    bool can_gain_level(CreaturePtr creature);

    uint get_experience_needed_for_level(CreaturePtr creature, const uint level);

    void level_up(CreaturePtr creature);
    void gain_level(CreaturePtr creature);
    void gain_hp_and_ap(CreaturePtr creature);
    void gain_statistics_if_necessary(CreaturePtr creature);
    void run_level_script(CreaturePtr creature);
    
    // The actual experience table
    static const uint base_experience_table[];
    static const int base_experience_table_size;
};
