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

DisplayInventoryMap InventoryTranslator::create_display_inventory(Inventory& inv)
{
  DisplayInventoryMap display_inventory;

  list<ItemPtr> raw_inv = inv.get_items();
  
  BOOST_FOREACH(ItemPtr item, raw_inv)
  {
    if (item)
    {
      ItemType item_type = item->get_type();
      DisplayItemTypePtr type = DisplayItemTypeFactory::create(item_type);
      
      vector<DisplayItem>* current_category = &display_inventory[*type];
      DisplayItem display_item = ItemTranslator::create_display_item(item);
      
      current_category->push_back(display_item);
    }
  }
  
  return display_inventory;
}
