#pragma once
#include "Creature.hpp"
#include "Display.hpp"

class EquipmentManager
{
  public:
    EquipmentManager(DisplayPtr new_display, CreaturePtr new_creature);
    ~EquipmentManager();

    bool manage_equipment();

  protected:
    DisplayPtr display;
    CreaturePtr creature;
};
