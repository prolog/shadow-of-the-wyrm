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

DisplayInventoryMap InventoryTranslator::create_display_inventory(const CreaturePtr& c)
{
  DisplayInventoryMap display_inventory = create_initial_display_inventory_categories();

  if (c)
  {
    Inventory inv = c->get_inventory();
    list<ItemPtr> raw_inv = inv.get_items();
    
    BOOST_FOREACH(ItemPtr item, raw_inv)
    {
      if (item)
      {
        ItemType item_type = item->get_type();
        DisplayItemTypePtr type = DisplayItemTypeFactory::create(item_type);
        vector<DisplayItem>* current_category = &display_inventory[type];

        DisplayItem display_item = ItemTranslator::create_display_item(item);
        
        current_category->push_back(display_item);
      }
    }
  }

  return display_inventory;
}

// Creates a DisplayInventoryMap with all the initial category vectors inserted (empty)
DisplayInventoryMap InventoryTranslator::create_initial_display_inventory_categories()
{
  DisplayInventoryMap display_inventory;
  
  for (int i = ITEM_TYPE_FIRST; i < ITEM_TYPE_LAST; i++)
  {
    vector<DisplayItem> display_items;
    DisplayItemTypePtr display_item_type = DisplayItemTypeFactory::create(static_cast<ItemType>(i));
    display_inventory[display_item_type] = display_items;
  }
  
  return display_inventory;
}
