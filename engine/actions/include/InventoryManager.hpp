#pragma once
#include "Creature.hpp"
#include "Display.hpp"
#include "DisplayItem.hpp"
#include "IActionManager.hpp"

class InventoryManager : public IActionManager
{
  public:
    InventoryManager(DisplayPtr new_display, CreaturePtr new_creature);
    ~InventoryManager();

    // Do the actual managing of the inventory
    ItemPtr manage_inventory(Inventory& inv, const bool inventory_is_read_only);

    // Select an item from the current 'page'.
    ItemPtr select_item(Inventory& inv, const DisplayInventoryMap& inventory_display, const uint item_index);

  protected:
    uint get_current_action_cost() const;

    DisplayPtr display;
    CreaturePtr creature;
    
    uint current_page_start; // The index in the inventory at which the current page starts
    uint current_page_size; // Returned from the display
};
