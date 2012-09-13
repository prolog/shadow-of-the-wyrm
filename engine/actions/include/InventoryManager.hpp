#pragma once
#include <list>
#include "Creature.hpp"
#include "Display.hpp"
#include "DisplayItem.hpp"
#include "IActionManager.hpp"
#include "IItemFilter.hpp"

class InventoryManager : public IActionManager
{
  public:
    InventoryManager(DisplayPtr new_display, CreaturePtr new_creature);
    ~InventoryManager();

    // Do the actual managing of the inventory
    ItemPtr manage_inventory(Inventory& inv, const std::list<IItemFilterPtr>& display_filter_list, const bool inventory_is_read_only);

    // Select an item from the current 'page'.
    ItemPtr select_item(Inventory& inv, const DisplayInventoryMap& inventory_display, const uint item_index);

  protected:
    ActionCostValue get_action_cost_value() const;

    DisplayPtr display;
    CreaturePtr creature;
    
    uint current_page_start; // The index in the inventory at which the current page starts
    uint current_page_size; // Returned from the display
};
