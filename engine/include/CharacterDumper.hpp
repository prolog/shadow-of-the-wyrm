#pragma once
#include <string>
#include "Creature.hpp"

class CharacterDumper
{
  public:
    CharacterDumper(CreaturePtr new_creature, const int new_num_cols = 80);
    ~CharacterDumper();
    
    std::string str() const;
    
  protected:
    // Functions to get smaller parts of the character's details, as strings.
    std::string get_synopsis() const;
    std::string get_vital_statistics() const;
    std::string get_stats() const;
    
    // Formatting functions.  FIXME: Maybe move these to String later.
    void reset_and_pad(std::string& string_to_reset_and_pad) const;
    
    std::string centre(const std::string& string_to_centre) const;
    std::string right (const std::string& string_to_right_justify) const;
  
    CreaturePtr creature;
    int num_cols;
};
