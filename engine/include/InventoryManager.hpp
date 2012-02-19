#pragma once
#include "Creature.hpp"
#include "Display.hpp"

class InventoryManager
{
  public:
    InventoryManager(DisplayPtr new_display, CreaturePtr new_creature);
    ~InventoryManager();

    ItemPtr manage_inventory();

  protected:
    DisplayPtr display;
    CreaturePtr creature;
};
