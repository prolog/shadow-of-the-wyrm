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

    // Handle adding a component to the current menu - add it, and then if the
    // current item count has reached the maximum, reset the count, add the
    // current menu to the list of pages, etc.
    void add_component(std::vector<MenuComponentPtr>& current_menu, MenuComponentPtr component, int& cnt);

    CreaturePtr creature;
    DisplayInventoryMap dim;
};
