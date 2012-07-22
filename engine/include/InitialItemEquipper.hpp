#pragma once
#include "Creature.hpp"
#include "InitialItemSelector.hpp"

class InitialItemEquipper
{
  public:
    void equip(CreaturePtr creature, ActionManager& am);
    void add_inventory_items(CreaturePtr creature, ActionManager& am);
};
