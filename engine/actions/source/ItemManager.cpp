#include "Game.hpp"
#include "ItemFactory.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"

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
    
    // JCD FIXME: Change this to an ItemFactory based on its type.
    new_item = ItemFactory::create(found_item);
  }
  
  return new_item;
}

ItemPtr ItemManager::create_item(const std::string& item_id)
{
  ItemPtr item;
  Game* game = Game::instance();
  
  if (game)
  {
    const ItemMap& items = game->get_items_ref();
    ItemManager manager;
    item = manager.create_item(items, item_id);
  }
  
  return item;
}

// Create an item with a certain probability, and add it to the given
// inventory.  If we don't pass the probability check, do nothing.
void ItemManager::create_item_with_probability(const int rand_less_than_or_equal_val, const int rand_upper_val, Inventory& inv, const std::string& item_id)
{
  int rand = RNG::range(1, rand_upper_val);
  if (rand <= rand_less_than_or_equal_val)
  {
    ItemPtr item = ItemManager::create_item(item_id);
    
    // Only add the item if it was created successfully
    if (item)
    {
      inv.add(item);
    }
  }
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
    dropped_item = inv.remove(item->get_id());
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
// Add it to the inventory.
ItemPtr ItemManager::remove(CreaturePtr creature, const EquipmentWornLocation location)
{
  ItemPtr item;
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    item = eq.remove_item(location);
    pick_up(creature, item);
  }
  
  return item;
}

ActionCostValue ItemManager::get_action_cost_value() const
{
  // JCD FIXME
  return 1;
}
