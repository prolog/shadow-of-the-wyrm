#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class DeathDumper : public StringConverter
{
  public:
    DeathDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    CreaturePtr creature;
    uint num_cols;
};

