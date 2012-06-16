#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

// A command processor that processes exclusively equipment-related
// commands.
class EquipmentCommandProcessor 
{
  public:
    static ActionCostValue process(CreaturePtr creature, CommandPtr command);

  protected:
    EquipmentCommandProcessor();
    ~EquipmentCommandProcessor();
};
