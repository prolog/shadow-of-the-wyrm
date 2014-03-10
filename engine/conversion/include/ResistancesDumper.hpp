#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class ResistancesDumper : public StringConverter
{
  public:
    ResistancesDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_resistances() const;

    CreaturePtr creature;
    uint num_cols;
};
