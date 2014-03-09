#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class SpellsDumper : public StringConverter
{
  public:
    SpellsDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_spells() const;

    CreaturePtr creature;
    uint num_cols;
};
