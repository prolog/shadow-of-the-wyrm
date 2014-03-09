#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class ConductsDumper : public StringConverter
{
  public:
    ConductsDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_conducts() const;

    CreaturePtr creature;
    uint num_cols;
};
