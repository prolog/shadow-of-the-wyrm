#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class MortuaryDumper : public StringConverter
{
  public:
    MortuaryDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_mortuary() const;

    CreaturePtr creature;
    uint num_cols;
};
