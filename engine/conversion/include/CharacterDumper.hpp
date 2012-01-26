#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class CharacterDumper : public StringConverter
{
  public:
    CharacterDumper(CreaturePtr new_creature, const uint new_num_cols = 80);
    ~CharacterDumper();
    
    std::string str() const;
    
  protected:
    // Functions to get smaller parts of the character's details, as strings.
    std::string get_synopsis() const;
    std::string get_vital_statistics() const;
    // Inventory
    // Items
      
    CreaturePtr creature;
    uint num_cols;
};
