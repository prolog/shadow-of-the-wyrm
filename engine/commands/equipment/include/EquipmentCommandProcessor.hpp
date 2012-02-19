#pragma once
#include "Creature.hpp"

// A command processor that processes exclusively equipment-related
// commands.
class EquipmentCommandProcessor 
{
  public:
    static bool process(CreaturePtr creature, CommandPtr command);

  protected:
    EquipmentCommandProcessor();
    ~EquipmentCommandProcessor();
};
