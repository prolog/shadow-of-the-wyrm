#pragma once
#include "Creature.hpp"
#include "DisplayItem.hpp"
#include "IItemFilter.hpp"

class InventoryManager;

// A command processor used for inventory processing
class InventoryCommandProcessor
{
  public:
    // inv_manager is for function calls during processing.
    static bool process(InventoryManager* const inv_manager, const std::list<IItemFilterPtr>& base_display_filter_list, const DisplayInventoryMap& inventory_display, const std::string& item_id, CreaturePtr creature, IInventoryPtr inv, CommandPtr command, const bool inventory_is_read_only, ItemPtr& selected_item);

  protected:
    InventoryCommandProcessor();
    ~InventoryCommandProcessor();
    
    static uint convert_keypress_to_item_index(const int keypress);
};
