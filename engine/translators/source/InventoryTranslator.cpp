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

DisplayInventoryMap InventoryTranslator::create_display_inventory(Inventory& inv, const EquipmentWornLocation ewl)
{
  DisplayInventoryMap display_inventory;

  list<ItemPtr> raw_inv = inv.get_items();
  
  BOOST_FOREACH(ItemPtr item, raw_inv)
  {
    if (item)
    {
      ItemType item_type = item->get_type();
      
      // Check to see if the item can be displayed.
      bool allow_category_squishiness = true;
      
      if (is_applicable_for_display(ewl, item->get_worn_location(), allow_category_squishiness))
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
bool InventoryTranslator::is_applicable_for_display(const EquipmentWornLocation slot_location, const EquipmentWornLocation item_location, const bool squishy_filter)
{
  if (!squishy_filter)
  {
    return (slot_location == item_location);
  }
  else
  {
    if (slot_location == item_location)
    {
      return true;
    }
    else
    {
      return check_squishy(slot_location, item_location);
    }
  }
}

// Check to see if items have similar slots, allowing squish.
bool InventoryTranslator::check_squishy(const EquipmentWornLocation slot_location, const EquipmentWornLocation item_ewl)
{
  bool squishy_ring  = ((slot_location == EQUIPMENT_WORN_RIGHT_FINGER) || (slot_location == EQUIPMENT_WORN_LEFT_FINGER));
  bool item_ring     = ((item_ewl == EQUIPMENT_WORN_RIGHT_FINGER) || (item_ewl == EQUIPMENT_WORN_LEFT_FINGER));

  bool squishy_wield = ((slot_location == EQUIPMENT_WORN_RIGHT_HAND) || (slot_location == EQUIPMENT_WORN_LEFT_HAND) || (slot_location == EQUIPMENT_WORN_AMMUNITION));
  bool item_wield    = ((item_ewl == EQUIPMENT_WORN_RIGHT_HAND) || (item_ewl == EQUIPMENT_WORN_LEFT_HAND) || (item_ewl == EQUIPMENT_WORN_AMMUNITION));

  return ((squishy_ring && item_ring) || (squishy_wield && item_wield));
}
