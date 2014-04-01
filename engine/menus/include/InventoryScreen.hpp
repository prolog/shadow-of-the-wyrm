#pragma once
#include <map>
#include "Creature.hpp"
#include "Menu.hpp"
#include "Display.hpp"
#include "IItemFilter.hpp"

class InventoryScreen : public Menu
{
  public:
    InventoryScreen(DisplayPtr display, CreaturePtr creature, const DisplayInventoryMap& new_dim);

  protected:
    void initialize() override;

    CreaturePtr creature;
    DisplayInventoryMap dim;
};
