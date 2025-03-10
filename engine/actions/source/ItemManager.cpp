#include <algorithm>
#include "CreatureUtils.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "EquipmentManager.hpp"
#include "ItemIdentifier.hpp"
#include "ItemFactory.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "Wearable.hpp"

using namespace std;

bool ItemManager::operator==(const ItemManager& /* im */) const
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

  for(const EquipmentMap::value_type& eq_pair : eq_map)
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
list<ItemPtr> ItemManager::get_items_by_type(const IInventoryPtr inv, const ItemType item_type)
{
  list<ItemPtr> result_items;

  const list<ItemPtr>& raw_items = inv->get_items_cref();

  for(ItemPtr item : raw_items)
  {
    if (item && item->get_type() == item_type)
    {
      result_items.push_front(item);
    }
  }

  return result_items;
}

list<ItemPtr> ItemManager::get_filtered_items(IInventoryPtr inv, const list<IItemFilterPtr>& filters)
{
  list<ItemPtr> result;

  if (inv != nullptr)
  {
    const list<ItemPtr> raw_items = inv->get_items_cref();
    back_insert_iterator<list<ItemPtr>> back_it(result);

    copy_if(raw_items.begin(), raw_items.end(), back_it,
      [filters](ItemPtr item)
      {
        bool pass_f = true;

        for (IItemFilterPtr i : filters)
        {
          pass_f = pass_f && i->passes_filter(item);
        }

        return pass_f;
      });
  }

  return result;
}

// Check to see if a creature has an item with the given base ID.
bool ItemManager::has_item(CreaturePtr creature, const string& base_item_id, const map<string, string>& properties)
{
  EquipmentMap eq_map = creature->get_equipment().get_equipment();

  for(const EquipmentMap::value_type& eq_pair : eq_map)
  {
    ItemPtr item = eq_pair.second;

    if (item && item->get_base_id() == base_item_id)
    {
      bool props_match = true;

      for (const auto& prop_pair : properties)
      {
        if (item->get_additional_property(prop_pair.first) != prop_pair.second)
        {
          props_match = false;
          break;
        }
      }

      if (props_match)
      {
        return true;
      }
    }
  }

  const list<ItemPtr>& raw_items = creature->get_inventory()->get_items_cref();

  for(ItemPtr item : raw_items)
  {
    if (item && item->get_base_id() == base_item_id)
    {
      bool props_match = true;

      for (const auto& prop_pair : properties)
      {
        if (item->get_additional_property(prop_pair.first) != prop_pair.second)
        {
          props_match = false;
          break;
        }
      }

      if (props_match)
      {
        return true;
      }
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
    // Create a new item based on the template.
    ItemPtr found_item = ItemPtr(i_it->second->create_with_new_id());

    // Check the item generation values to see if we can create the
    // item, based on the current max.
    Game& game = Game::instance();
    GenerationValuesMap& igv_map = game.get_item_generation_values_ref();
    GenerationValuesMap::iterator gv_it = igv_map.find(item_id);

    if (gv_it != igv_map.end())
    {
      GenerationValues& igv = gv_it->second;
      if (!igv.is_maximum_reached())
      {
        igv.incr_current();

        new_item = ItemFactory::create(found_item);
        new_item->set_quantity(quantity);
      }
      else
      {
        Log::instance().debug("ItemManager::create_item - tried to add item with ID " + item_id + ", but the maximum was reached.  Returning null ItemPtr.");
      }
    }  
    else
    {
      Log::instance().error("ItemManager::create_item - Couldn't find item generation values for item with ID " + item_id);
    }
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

// Remove an item or reduce the quantity by 1.  First check the inventory, and
// then the equipment.
pair<bool, vector<ItemPtr>> ItemManager::remove_item_from_inv_or_eq(CreaturePtr creature, const string& base_item_id, const int quantity, const map<string, string>& properties)
{
  pair<bool, vector<ItemPtr>> result;
  result.first = false;

  int rem_quantity = quantity;

  Equipment& eq  = creature->get_equipment();
  IInventoryPtr inv = creature->get_inventory();

  EquipmentMap eq_map = eq.get_equipment();
  pair<bool, vector<ItemPtr>> inv_items = inv->remove_by_base_id(base_item_id, rem_quantity, properties);

  for (const auto& inv_it_it : inv_items.second)
  {
    rem_quantity -= static_cast<int>(inv_it_it->get_quantity());
  }

  if (rem_quantity > 0)
  {
    for (const EquipmentMap::value_type& eq_pair : eq_map)
    {
      ItemPtr item = eq_pair.second;

      if (item && item->get_base_id() == base_item_id && item->has_additional_properties(properties))
      {
        int i_quantity = item->get_quantity();
        bool remove_item = (i_quantity <= rem_quantity);
        int num_to_remove = (i_quantity >= rem_quantity ? rem_quantity : i_quantity);
        rem_quantity -= (i_quantity >= rem_quantity ? rem_quantity : i_quantity);

        if (remove_item)
        {
          // Subtract the current quantity from what's remaining, and
          // remove the item.

          // Don't transfer to inventory
          ItemPtr cur_item = remove(creature, eq_pair.first, false);
          result.second.push_back(cur_item);
        }
        else
        {
          // There are more items than are needed for removal.
          // Reduce the quantity accordingly.
          int existing_item_new_quantity = i_quantity - num_to_remove;
          int new_item_quantity = num_to_remove;

          ItemPtr new_item = ItemPtr(item->clone_with_new_id());
          item->set_quantity(existing_item_new_quantity);
          new_item->set_quantity(new_item_quantity);

          result.second.push_back(new_item);
        }

        result.first = true;

        if (rem_quantity <= 0)
        {
          break;
        }
      }
    }
  }

  result.first = inv_items.first;
  result.second = inv_items.second;

  return result;
}

// Create an item with a certain probability, and add it to the given
// inventory.  If we don't pass the probability check, do nothing.
bool ItemManager::create_item_with_probability(const int rand_less_than_or_equal_val, const int rand_upper_val, IInventoryPtr inv, const std::string& item_id, const uint quantity, const bool disallow_cursed)
{
  // For safety's sake, always do nothing and return false when the item id
  // is empty.
  if (item_id.empty() || (rand_upper_val == 0) || (rand_upper_val < rand_less_than_or_equal_val))
  {
    return false;
  }

  int rand = RNG::range(1, rand_upper_val);
  if (rand <= rand_less_than_or_equal_val)
  {
    ItemPtr item = ItemManager::create_item(item_id, quantity);
    
    // Only add the item if it was created successfully
    if (item)
    {
      if (disallow_cursed && item->get_status() == ItemStatus::ITEM_STATUS_CURSED)
      {
        item->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
      }

      inv->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);

      return true;
    }
  }

  return false;
}

ActionCostValue ItemManager::pick_up(CreaturePtr creature, ItemPtr item)
{
  ActionCostValue picked_up_item = ActionCostConstants::NO_ACTION;
  
  if (creature && item)
  {
    IInventoryPtr inv = creature->get_inventory();
    inv->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);

    picked_up_item = get_action_cost_value(creature);
  }
  
  return picked_up_item;
}

ActionCostValue ItemManager::drop(CreaturePtr dropping_creature, ItemPtr item)
{
  ActionCostValue dropped_item = ActionCostConstants::NO_ACTION;
  
  if (dropping_creature && item)
  {
    IInventoryPtr inv = dropping_creature->get_inventory();
    
    if (inv->remove(item->get_id()))
    {
      dropped_item = get_action_cost_value(dropping_creature);
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
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
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

    if (action_cost_value > 0 && item)
    {
      WearablePtr wearable = dynamic_pointer_cast<Wearable>(item);
      CreatureUtils::apply_status_ailments(wearable, creature);
    }
  }
  
  return action_cost_value; 
}

// Equip the item.  If successful, remove it from the inventory, and then
// identify the item, if the item is a wearable.
ActionCostValue ItemManager::equip_and_remove_from_inventory(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    
    if (eq.set_item(item, eq_worn_slot))
    {
      handle_item_identification_and_statuses(creature, item);

      // Remove from inventory.
      action_cost_value = get_action_cost_value(creature);

      string item_id = item->get_id();
      creature->get_inventory()->remove(item_id);
    }
  }
    
  return action_cost_value;
}

// Equip the item.  If successful, reduce the amount in the inventory by the quantity of the item.
ActionCostValue ItemManager::equip_and_reduce_inventory_quantity(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot, const uint quantity)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    
    ItemPtr new_item = ItemPtr(item->create_with_new_id());
    
    if (eq.set_item(new_item, eq_worn_slot))
    {
      new_item->set_quantity(1);
      item->set_quantity(quantity-1);
      uint inv_item_quantity = item->get_quantity();
      
      if (inv_item_quantity == 0) creature->get_inventory()->remove(item->get_id());
      
      handle_item_identification_and_statuses(creature, new_item);

      action_cost_value = ActionCostConstants::DEFAULT;
    }
  }
  
  return action_cost_value;
}

ActionCostValue ItemManager::equip(CreaturePtr creature, ItemPtr item)
{
  ActionCostValue equipped_item = ActionCostConstants::NO_ACTION;
  
  if (creature && item)
  {
    equipped_item = equip(creature, item, item->get_worn_location());
  }
  
  return equipped_item;
}

void ItemManager::handle_item_identification_and_statuses(CreaturePtr creature, ItemPtr item)
{
  if (item != nullptr)
  {
    if (item->get_artifact())
    {
      creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_ARTIFACTLESS);
    }

    ItemIdentifier iid;

    if (creature->get_is_player())
    {
      iid.set_item_identified(creature, item, item->get_base_id(), true);
    }

    // If auto-cursing, curse it.
    if (item->get_auto_curse())
    {
      item->set_status(ItemStatus::ITEM_STATUS_CURSED);

      if (creature->get_is_player())
      {
        item->set_status_identified(true);
      }
    }
  }
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

    WearablePtr wearable = dynamic_pointer_cast<Wearable>(item);
    CreatureUtils::remove_status_ailments_from_wearable(wearable, creature);
    
    if (transfer_to_inventory)
    {
      pick_up(creature, item);
    }
  }
  
  return item;
}

ActionCostValue ItemManager::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 1;
}
