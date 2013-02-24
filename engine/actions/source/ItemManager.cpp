#include <algorithm>
#include <boost/foreach.hpp>
#include "Game.hpp"
#include "EquipmentManager.hpp"
#include "ItemFactory.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"

using namespace std;

bool ItemManager::operator==(const ItemManager& im)
{
  return true;
}

// Get all items of a certain type from a creature's equipment and inventory.
list<ItemPtr> ItemManager::get_items_by_type(CreaturePtr creature, const ItemType item_type)
{
  list<ItemPtr> all_items;

  list<ItemPtr> eq_items = get_items_by_type(creature->get_equipment(), item_type);
  list<ItemPtr> inv_items = get_items_by_type(creature->get_inventory(), item_type);

  all_items.insert(all_items.begin(), eq_items.begin(), eq_items.end());
  all_items.insert(all_items.begin(), inv_items.begin(), inv_items.end());

  return all_items;
}

// Get all items of a certain type from a given set of equipment.
list<ItemPtr> ItemManager::get_items_by_type(const Equipment& eq, const ItemType item_type)
{
  list<ItemPtr> result_items;
 
  EquipmentMap eq_map = eq.get_equipment();

  BOOST_FOREACH(EquipmentMap::value_type& eq_pair, eq_map)
  {
    ItemPtr item = eq_pair.second;

    if (item && item->get_type() == item_type)
    {
      result_items.push_front(item);
    }
  }

  return result_items;
}

// Get all items of a certain type from a given set of inventory.
list<ItemPtr> ItemManager::get_items_by_type(const Inventory& inv, const ItemType item_type)
{
  list<ItemPtr> result_items;

  list<ItemPtr> raw_items = inv.get_items_const();

  BOOST_FOREACH(ItemPtr item, raw_items)
  {
    if (item && item->get_type() == item_type)
    {
      result_items.push_front(item);
    }
  }

  return result_items;
}

// Check to see if a creature has an item with the given base ID.
bool ItemManager::has_item(CreaturePtr creature, const string& base_item_id)
{
  EquipmentMap eq_map = creature->get_equipment().get_equipment();

  BOOST_FOREACH(EquipmentMap::value_type& eq_pair, eq_map)
  {
    ItemPtr item = eq_pair.second;

    if (item && item->get_base_id() == base_item_id)
    {
      return true;
    }
  }

  list<ItemPtr> raw_items = creature->get_inventory().get_items_const();

  BOOST_FOREACH(ItemPtr item, raw_items)
  {
    if (item && item->get_base_id() == base_item_id)
    {
      return true;
    }
  }

  return false;
}

// Create a new shared pointer to an Item, given the items in the game,
// and the ID of the item to create.
ItemPtr ItemManager::create_item(const ItemMap& items, const std::string& item_id, const uint quantity)
{
  ItemPtr new_item;
  
  ItemMap::const_iterator i_it = items.find(item_id);
  if (i_it != items.end())
  {
    ItemPtr found_item = i_it->second;
    
    // JCD FIXME: Change this to an ItemFactory based on its type.
    new_item = ItemFactory::create(found_item);
    new_item->set_quantity(quantity);
  }
  
  return new_item;
}

ItemPtr ItemManager::create_item(const std::string& item_id, const uint quantity)
{
  ItemPtr item;
  Game& game = Game::instance();
  
  const ItemMap& items = game.get_items_ref();
  ItemManager manager;
  item = manager.create_item(items, item_id, quantity);
  
  return item;
}

// Remove an item or reduce the quantity by 1.  First check the equipment, and
// then the inventory.
bool ItemManager::remove_item_from_eq_or_inv(CreaturePtr creature, const string& base_item_id)
{
  Equipment& eq  = creature->get_equipment();
  Inventory& inv = creature->get_inventory();

  EquipmentMap eq_map = eq.get_equipment();

  BOOST_FOREACH(EquipmentMap::value_type& eq_pair, eq_map)
  {
    ItemPtr item = eq_pair.second;

    if (item && item->get_base_id() == base_item_id)
    {
      uint quantity = item->get_quantity();
      if (quantity > 1)
      {
        item->set_quantity(quantity-1);
      }
      else
      {
        // Don't transfer to inventory, and swallow the returned ItemPtr
        remove(creature, eq_pair.first, false);
      }

      return true;
    }
  }

  return inv.remove_by_base_id(base_item_id);

  return false;
}

// Create an item with a certain probability, and add it to the given
// inventory.  If we don't pass the probability check, do nothing.
void ItemManager::create_item_with_probability(const int rand_less_than_or_equal_val, const int rand_upper_val, Inventory& inv, const std::string& item_id, const uint quantity)
{
  int rand = RNG::range(1, rand_upper_val);
  if (rand <= rand_less_than_or_equal_val)
  {
    ItemPtr item = ItemManager::create_item(item_id, quantity);
    
    // Only add the item if it was created successfully
    if (item)
    {
      inv.merge_or_add(item, INVENTORY_ADDITION_BACK);
    }
  }
}

ActionCostValue ItemManager::pick_up(CreaturePtr creature, ItemPtr item)
{
  ActionCostValue picked_up_item = 0;
  
  if (creature && item)
  {
    Inventory& inv = creature->get_inventory();
    inv.merge_or_add(item, INVENTORY_ADDITION_BACK);

    picked_up_item = get_action_cost_value();
  }
  
  return picked_up_item;
}

ActionCostValue ItemManager::drop(CreaturePtr creature, ItemPtr item)
{
  ActionCostValue dropped_item = 0;
  
  if (creature && item)
  {
    Inventory& inv = creature->get_inventory();
    
    if (inv.remove(item->get_id()))
    {
      dropped_item = get_action_cost_value();
    }
  }
  
  return dropped_item;
}

// Add the item to the creature's list of equipped items.
// By default, try to equip to the slot specified in the ItemPtr.
// The override is so that an item can be equipped to a similar slot:
// e.g., left hand instead of right hand.
ActionCostValue ItemManager::equip(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature && item)
  {
    Equipment& eq = creature->get_equipment();
    bool slot_allows_multiple_items = eq.can_equip_multiple_items(eq_worn_slot);
    
    // Case 1: slot allows multiple items.  Equip the entire heap.
    if (slot_allows_multiple_items)
    {
      action_cost_value = equip_and_remove_from_inventory(creature, item, eq_worn_slot);
    }
    else
    {
      uint quantity = item->get_quantity();
      
      // Case 2: slot requires single item, item quantity = 1
      if (quantity == 1)
      {
        action_cost_value = equip_and_remove_from_inventory(creature, item, eq_worn_slot);
      }
      // Case 3: slot requires single item, item quantity > 1 (create a copy with a new id)
      else
      {
        action_cost_value = equip_and_reduce_inventory_quantity(creature, item, eq_worn_slot, quantity);
      }
    }    
  }
  
  return action_cost_value; 
}

// Equip the item.  If successful, remove it from the inventory.
ActionCostValue ItemManager::equip_and_remove_from_inventory(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    
    if (eq.set_item(item, eq_worn_slot))
    {
      action_cost_value = get_action_cost_value();

      string item_id = item->get_id();
      creature->get_inventory().remove(item_id);
    }
  }
    
  return action_cost_value;
}

// Equip the item.  If successful, reduce the amount in the inventory by the quantity of the item.
ActionCostValue ItemManager::equip_and_reduce_inventory_quantity(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot, const uint quantity)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    
    ItemPtr new_item = ItemPtr(item->clone_with_new_id());
    
    if (eq.set_item(new_item, eq_worn_slot))
    {
      new_item->set_quantity(1);
      item->set_quantity(quantity-1);
      uint inv_item_quantity = item->get_quantity();
      
      if (inv_item_quantity == 0) creature->get_inventory().remove(item->get_id());
      
      action_cost_value = 1;
    }
  }
  
  return action_cost_value;
}

ActionCostValue ItemManager::equip(CreaturePtr creature, ItemPtr item)
{
  ActionCostValue equipped_item = 0;
  
  if (creature && item)
  {
    equipped_item = equip(creature, item, item->get_worn_location());
  }
  
  return equipped_item;
}

// Remove an item from a particular slot in the creature's equipment.
// Add it to the inventory.
ItemPtr ItemManager::remove(CreaturePtr creature, const EquipmentWornLocation location, bool transfer_to_inventory)
{
  ItemPtr item;
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    item = eq.remove_item(location);
    
    if (transfer_to_inventory)
    {
      pick_up(creature, item);
    }
  }
  
  return item;
}

ActionCostValue ItemManager::get_action_cost_value() const
{
  // JCD FIXME
  return 1;
}
