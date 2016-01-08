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
    ItemPtr manage_inventory(IInventoryPtr inv, const std::list<IItemFilterPtr>& base_display_filter_list, const std::list<IItemFilterPtr>& additional_display_filter_list, const bool inventory_is_read_only);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    DisplayPtr display;
    CreaturePtr creature;
    
    uint current_page_start; // The index in the inventory at which the current page starts
    uint current_page_size; // Returned from the display
};
