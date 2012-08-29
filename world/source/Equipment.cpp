#include "Equipment.hpp"

Equipment::Equipment()
{
  initialize();
}

Equipment::~Equipment()
{
  
}

// Set an item, but only if it's not null.  There are no checks done here to 
// see if the slot is correct - that's a higher-level check.
bool Equipment::set_item(ItemPtr item, const EquipmentWornLocation worn_location)
{
  bool item_set = false;
  
  if (item)
  {
    equipment[worn_location] = item;
    item_set = true;
  }
  
  return item_set;
}

// Get the item being worn in a certain slot.
ItemPtr Equipment::get_item(const EquipmentWornLocation worn_location) const
{
  ItemPtr current_item;
  EquipmentMap::const_iterator c_it = equipment.find(worn_location);
  
  if (c_it != equipment.end())
  {
    current_item = c_it->second;
  }

  return current_item;
}

// Remove an item from a particular slot, and return it.
ItemPtr Equipment::remove_item(const EquipmentWornLocation worn_location)
{
  ItemPtr previously_worn_item = equipment[worn_location];
  ItemPtr no_item;
  
  if (previously_worn_item)
  {
    equipment[worn_location] = no_item;
  }
  
  return previously_worn_item;
}

// Initialize the internal map of items.
void Equipment::initialize()
{
  equipment.clear();
  
  for (EquipmentWornLocation worn_location = EQUIPMENT_WORN_HEAD; worn_location < EQUIPMENT_WORN_LAST; worn_location++)
  {
    ItemPtr no_item;
    equipment[worn_location] = no_item;
  }
}

// Check to see if a heap of items can be equipped
bool Equipment::can_equip_multiple_items(const EquipmentWornLocation ewl) const
{
  return (ewl == EQUIPMENT_WORN_AMMUNITION);
}

// Get the current set of equipment.
EquipmentMap Equipment::get_equipment() const
{
  return equipment;
}
