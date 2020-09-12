#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class ModifiersDumper : public StringConverter
{
  public:
    ModifiersDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_modifiers() const;

    CreaturePtr creature;
    uint num_cols;
};
