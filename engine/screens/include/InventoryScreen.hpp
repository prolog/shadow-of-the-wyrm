#pragma once
#include <map>
#include "Creature.hpp"
#include "Screen.hpp"
#include "Display.hpp"
#include "IItemFilter.hpp"

class InventoryScreen : public Screen
{
  public:
    InventoryScreen(DisplayPtr display, CreaturePtr creature, const DisplayInventoryMap& new_dim, const bool user_filters, const bool inventory_is_read_only);

  protected:
    void initialize() override;

    CreaturePtr creature;
    DisplayInventoryMap dim;
    bool filters;
	bool read_only;
};
