#pragma once
#include "Creature.hpp"

class ExperienceManager
{
  public:
    ExperienceManager();
    ~ExperienceManager();

    bool gain_experience(CreaturePtr creature, const uint experience_value);
    
  protected:
    bool can_gain_level(CreaturePtr creature);
    void gain_level(CreaturePtr creature);
    
    // The actual experience table
    static const uint base_experience_table[];
    static const int base_experience_table_size;
};
