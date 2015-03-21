#pragma once
#include "Creature.hpp"
#include "CreatureGenerationValues.hpp"
#include "InitialItemSelector.hpp"

class InitialItemEquipper
{
  public:
    void equip(CreaturePtr creature, const CreatureGenerationValues& cgv, ActionManager& am);
    void add_inventory_items(CreaturePtr creature, const CreatureGenerationValues& cgv, ActionManager& am);

  protected:
    void process_initial_equipment(CreaturePtr creature, const std::map<EquipmentWornLocation, InitialItem>& initial_eq, ActionManager& am);
    void process_initial_inventory(CreaturePtr creature, const std::vector<InitialItem>& initial_inv, ActionManager& am);
};
