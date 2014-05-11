#pragma once
#include <map>
#include "Creature.hpp"
#include "Screen.hpp"
#include "Display.hpp"
#include "IItemFilter.hpp"

class InventoryScreen : public Screen
{
  public:
    InventoryScreen(DisplayPtr display, CreaturePtr creature, const DisplayInventoryMap& new_dim);

  protected:
    void initialize() override;

    CreaturePtr creature;
    DisplayInventoryMap dim;
};
