#include "ItemManager.hpp"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

// Create a new shared pointer to an Item, given the items in the game,
// and the ID of the item to create.
ItemPtr ItemManager::create_item(const ItemMap& items, const std::string& item_id)
{
  ItemPtr new_item;
  
  ItemMap::const_iterator i_it = items.find(item_id);
  if (i_it != items.end())
  {
    ItemPtr found_item = i_it->second;
    new_item = ItemPtr(new Item(*found_item));
  }
  
  return new_item;
}

bool ItemManager::pick_up(CreaturePtr creature, ItemPtr item)
{
  bool picked_up_item = false;
  
  if (creature && item)
  {
    Inventory& inv = creature->get_inventory();
    picked_up_item = inv.add(item);
  }
  
  return picked_up_item;
}

bool ItemManager::drop(CreaturePtr creature, ItemPtr item)
{
  bool dropped_item = false;
  
  if (creature && item)
  {
    Inventory& inv = creature->get_inventory();
    dropped_item = inv.remove(item);
  }
  
  return dropped_item;
}

// Add the item to the creature's list of equipped items.
// By default, try to equip to the slot specified in the ItemPtr.
// The override is so that an item can be equipped to a similar slot:
// e.g., left hand instead of right hand.
bool ItemManager::equip(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot)
{
  bool equipped_item = false;
  
  if (creature && item)
  {
    Equipment& eq = creature->get_equipment();
    equipped_item = eq.set_item(item, eq_worn_slot);
  }
  
  return equipped_item;  
}

bool ItemManager::equip(CreaturePtr creature, ItemPtr item)
{
  bool equipped_item = false;
  
  if (creature && item)
  {
    equipped_item = equip(creature, item, item->get_worn_location());
  }
  
  return equipped_item;
}

// Remove an item from a particular slot in the creature's equipment.
ItemPtr ItemManager::remove(CreaturePtr creature, const EquipmentWornLocation location)
{
  ItemPtr item;
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    item = eq.remove_item(location);
  }
  
  return item;
}
