#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class InventoryDumper : public StringConverter
{
  public:
    InventoryDumper(CreaturePtr new_creature, const uint new_num_cols);

    std::string str() const;

  protected:
    std::string get_inventory() const;
    CreaturePtr creature;
    uint num_cols;
};
