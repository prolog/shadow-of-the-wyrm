#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class VictoryDumper : public StringConverter
{
  public:
    VictoryDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_wins() const;

    CreaturePtr creature;
    uint num_cols;
};

