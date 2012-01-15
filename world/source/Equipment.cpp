#include "Equipment.hpp"

Equipment::Equipment()
{
  initialize();
}

Equipment::~Equipment()
{
  
}

// Set an item, but only if it's not null, and if the worn location matches
// the slot we're trying to set.
bool Equipment::set_item(ItemPtr item, const EquipmentWornLocation worn_location)
{
  bool item_set = false;
  
  if (item && (worn_location == item->get_worn_location()))
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
  std::map<EquipmentWornLocation, ItemPtr>::const_iterator c_it = equipment.find(worn_location);
  
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
