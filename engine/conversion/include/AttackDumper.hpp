#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class AttackDumper : public StringConverter
{
  public:
    AttackDumper(CreaturePtr new_creature, const uint new_num_cols);

    std::string str() const override;

  protected:
    CreaturePtr creature;
    uint num_cols;
};
