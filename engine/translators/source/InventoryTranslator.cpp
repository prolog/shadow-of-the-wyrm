#include <boost/foreach.hpp>
#include "DisplayItemTypeFactory.hpp"
#include "InventoryTranslator.hpp"
#include "ItemTranslator.hpp"
#include "StringTable.hpp"

using namespace std;

InventoryTranslator::InventoryTranslator()
{
}

InventoryTranslator::~InventoryTranslator()
{
}

DisplayInventoryMap InventoryTranslator::create_display_inventory(Inventory& inv, const list<IItemDisplayFilterPtr>& display_filter_list)
{
  DisplayInventoryMap display_inventory;

  list<ItemPtr> raw_inv = inv.get_items();
  
  BOOST_FOREACH(ItemPtr item, raw_inv)
  {
    if (item)
    {
      ItemType item_type = item->get_type();
      
      if (is_applicable_for_display(item, display_filter_list))
      {
        DisplayItemTypePtr type = DisplayItemTypeFactory::create(item_type);
        
        vector<DisplayItem>* current_category = &display_inventory[*type];
        DisplayItem display_item = ItemTranslator::create_display_item(item);
        
        current_category->push_back(display_item);
      }      
    }
  }
  
  return display_inventory;
}

// Check to see if an item can be displayed.
//
// If the squishy filter is false, then the types must match exactly.  Otherwise, similar slots (left hand/right hand/ammunition, or right
// finger/left finger).
bool InventoryTranslator::is_applicable_for_display(ItemPtr item, const list<IItemDisplayFilterPtr>& display_filter_list)
{
  BOOST_FOREACH(IItemDisplayFilterPtr display_filter, display_filter_list)
  {
    if (!display_filter->passes_filter(item))
    {
      return false;
    }
  }

  // All the display filters have passed, so the item is applicable for display.
  return true;
}
