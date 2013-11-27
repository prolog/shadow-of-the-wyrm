#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class StatsDumper : public StringConverter
{
  public:
    StatsDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_stats() const;

    CreaturePtr creature;
    uint num_cols;
};
