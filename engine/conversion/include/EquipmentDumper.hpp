#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class EquipmentDumper : public StringConverter
{
  public:
    EquipmentDumper(CreaturePtr new_creature, const uint new_num_cols);

    std::string str() const override;

  protected:
    std::string get_equipment() const;
    
    CreaturePtr creature;
    uint num_cols;
};
