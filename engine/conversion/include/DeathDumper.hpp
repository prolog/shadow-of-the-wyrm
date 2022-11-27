#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class DeathDumper : public StringConverter
{
  public:
    DeathDumper(CreaturePtr new_creature, const bool new_narrative_mode, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    CreaturePtr creature;
    bool narrative_mode;
    uint num_cols;
};

