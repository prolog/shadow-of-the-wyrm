#pragma once
#include "Creature.hpp"
#include "CreatureGenerationValues.hpp"
#include "InitialItemSelector.hpp"

class InitialItemEquipper
{
  public:
    void equip(CreaturePtr creature, const CreatureGenerationValues& cgv, ActionManager& am);
    void add_inventory_items(CreaturePtr creature, const CreatureGenerationValues& cgv, ActionManager& am);
};
