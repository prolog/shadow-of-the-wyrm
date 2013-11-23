#include "IItemFilter.hpp"
#include "InventoryCommandFactory.hpp"
#include "InventoryCommandProcessor.hpp"
#include "InventoryKeyboardCommandMap.hpp"
#include "InventoryManager.hpp"
#include "InventoryTranslator.hpp"

using namespace std;

InventoryManager::InventoryManager(DisplayPtr new_display, CreaturePtr new_creature)
: display(new_display), creature(new_creature), current_page_start(0), current_page_size(0)
{
}

InventoryManager::~InventoryManager()
{
}

// If the inventory is read-only, the items can be viewed, but not selected.  This is for use in the "y" - View your inventory
// mode.  If the inventory is not read-only, items can be selected.
ItemPtr InventoryManager::manage_inventory(Inventory& inv, const list<IItemFilterPtr>& display_filter_list, const bool inventory_is_read_only)
{
  ItemPtr selected_item;
  bool manage_inv = true;
  ulonglong menus_created = 0;

  try
  {
    if (creature)
    {
      CommandFactoryPtr command_factory    = std::make_shared<InventoryCommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_shared<InventoryKeyboardCommandMap>();
    
      while (manage_inv)
      {
        DisplayInventoryMap display_inventory;
      
        if (display && creature->get_is_player())
        {
          display_inventory = InventoryTranslator::create_display_inventory(creature, inv, display_filter_list);
          current_page_size = display->display_inventory(display_inventory);
          menus_created++;
        }

        DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
        if (decision_strategy)
        {
          CommandPtr inventory_command = decision_strategy->get_decision(true, creature->get_id(), command_factory, kb_command_map);
          manage_inv = InventoryCommandProcessor::process(this, display_inventory, creature, inv, inventory_command, inventory_is_read_only, selected_item);        
        }
        else
        {
          manage_inv = false;
        }
      }
    }
  }
  catch(...)
  {
  }
  
  if (creature->get_is_player())
  {
    for (ulonglong i = 0; i < menus_created; i++)
    {
      display->clear_menu();
    } 
  }

  return selected_item;
}

ItemPtr InventoryManager::select_item(Inventory& inv, const DisplayInventoryMap& inventory_display, const uint index_in_current_page)
{
  ItemPtr selected_item;
  uint internal_index = 0;
  
  if ((index_in_current_page < current_page_size) && creature)
  {
    internal_index = current_page_start + index_in_current_page;
    
    // Get the display item
    uint search_ix = 0;
    for (DisplayInventoryMap::const_iterator d_it = inventory_display.begin(); d_it != inventory_display.end(); d_it++)
    {
      vector<DisplayItem> items = d_it->second;
      
      for(const DisplayItem& display_item : items)
      {
        if (search_ix == internal_index)
        {
          string id = display_item.get_id();
          selected_item = inv.get_from_id(id);
          return selected_item;
        }
        search_ix++;
      }
    }    
  }
  
  return selected_item;
}

ActionCostValue InventoryManager::get_action_cost_value() const
{
  return 1;
}
