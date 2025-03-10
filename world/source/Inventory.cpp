#include "Inventory.hpp"
#include "ItemSerializationFactory.hpp"
#include "Serialize.hpp"

using namespace std;

Inventory::Inventory()
: restack(false)
{
}

bool Inventory::operator==(const IInventory& inv) const
{
  bool result = true;

  size_t num_items = items.size();

  result = (num_items == (inv.get_items_cref()).size());

  if (result)
  {
    const list<ItemPtr>& items_b = inv.get_items_cref();
    list<ItemPtr>::const_iterator lista_it = items.begin();
    list<ItemPtr>::const_iterator listb_it = items_b.begin();

    while ((lista_it != items.end()) && (listb_it != items_b.end()))
    {
      ItemPtr item_a = *lista_it;
      ItemPtr item_b = *listb_it;

      result = result && (*item_a == *item_b);

      if (!result) break;
      
      lista_it++;
      listb_it++;
    }

    // Intentionally not including "restack".
    // Two inventories are equal if they have the same items/etc.
    // That one is flagged for restacking and one isn't shouldn't play into
    // equality.
  }

  return result;
}

AllowsItemsType Inventory::get_allows_items() const
{
  return AllowsItemsType::ALLOWS_ITEMS;
}

void Inventory::mark_for_restack()
{
  restack = true;
}

bool Inventory::get_marked_for_restack() const
{
  return restack;
}

// Add an item to the front of the inventory.  "add" is usually
// used for creatures; "add_front" for tiles, to get stack-like
// behaviour
bool Inventory::add_front(ItemPtr item)
{
  bool added_item = false;
  
  if (items.size() < items.max_size() && item != nullptr)
  {
    items.push_front(item);
    added_item = true;
  }
  
  return added_item;
}

// Add an item to the Inventory
bool Inventory::add(ItemPtr item)
{
  bool added_item = false;
  
  if (items.size() < items.max_size() && item != nullptr)
  {
    // JCD FIXME: Eventually, this should be an insert into the correct position.
    // Maybe.
    items.push_back(item);
    added_item = true;
  }
  
  return added_item;
}

bool Inventory::merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc)
{
  bool added = merge(item);
  if (!added)
  {
    switch(inv_add_loc)
    {
      case InventoryAdditionType::INVENTORY_ADDITION_FRONT:
        added = add_front(item);
        break;
      case InventoryAdditionType::INVENTORY_ADDITION_BACK:
      default:
        added = add(item);
        break;
    }
  }

  return added;
}

bool Inventory::merge_or_add(IInventoryPtr it, const InventoryAdditionType inv_add_loc)
{
  return merge_or_add(it.get(), inv_add_loc);
}

bool Inventory::merge_or_add(IInventory* it, const InventoryAdditionType inv_add_loc)
{
  if (it == nullptr || (*it == *this))
  {
    return false;
  }

  const list<ItemPtr> raw_items = it->get_items_cref();

  for (ItemPtr i : raw_items)
  {
    merge_or_add(i, inv_add_loc);
  }

  return true;
}

bool Inventory::transfer_to(IInventoryPtr it)
{
  if (it == nullptr || (*it == *this))
  {
    return false;
  }

  bool merged = it->merge_or_add(this, InventoryAdditionType::INVENTORY_ADDITION_BACK);
  clear();

  return merged;
}

bool Inventory::merge(ItemPtr it)
{
  for (ItemPtr inv_item : items)
  {
    if (inv_item && inv_item->matches(it))
    {
      // Pick up the item by adding the picked up item's quantity to the
      // current item's quantity.
      uint quantity = inv_item->get_quantity() + it->get_quantity();
      inv_item->set_quantity(quantity);
      
      // Merged successfully:
      return true;
    }
  }

  return false;
}

ItemPtr Inventory::remove_and_return(const string& id)
{
  ItemPtr item;

  if (items.size() > 0)
  {
    for (list<ItemPtr>::iterator item_it = items.begin(); item_it != items.end(); item_it++)
    {
      ItemPtr current_item = *item_it;

      if (current_item && (current_item->get_id() == id))
      {
        item = current_item;
        items.erase(item_it);
        break;
      }
    }
  }

  return item;
}

bool Inventory::remove(const string& id)
{
  if (items.size() > 0)
  {
    for (list<ItemPtr>::iterator item_it = items.begin(); item_it != items.end(); item_it++)
    {
      ItemPtr current_item = *item_it;
      
      if (current_item && (current_item->get_id() == id))
      {
        items.erase(item_it);
        return true;
      }
    }    
  }
  
  return false;
}

pair<bool, vector<ItemPtr>> Inventory::remove_by_base_id(const string& base_id, const int quantity, const map<string, string>& properties)
{
  pair<bool, vector<ItemPtr>> result = { false, {} };

  int rem_quantity = quantity;

  if (items.size() > 0)
  {
    list<ItemPtr>::iterator item_it = items.begin();

    while (item_it != items.end())
    {
      bool erased = false;

      ItemPtr current_item = *item_it;
      
      if (current_item && (current_item->get_base_id() == base_id) && current_item->has_additional_properties(properties))
      {
        result.first = true;
        int i_quantity = current_item->get_quantity();

        if (i_quantity <= rem_quantity)
        {
          result.second.push_back(current_item);
          items.erase(item_it++);
          erased = true;
        }
        else
        {
          int new_quantity = rem_quantity;

          ItemPtr new_item = ItemPtr(current_item->clone_with_new_id());
          new_item->set_quantity(new_quantity);

          current_item->set_quantity(i_quantity - rem_quantity);

          result.second.push_back(new_item);
        }

        rem_quantity -= i_quantity;

        if (rem_quantity <= 0)
        {
          break;
        }
      }

      if (!erased)
      { 
        item_it++;
      }
    }    
  }

  return result;
}

// Count the number of items in the inventory, excluding currency, which does
// not count towards the max.
uint Inventory::count_items() const
{
  uint count = 0;
  const list<ItemPtr> it = get_items_cref();

  for (ItemPtr item : it)
  {
    if (item != nullptr && (item->get_type() != ItemType::ITEM_TYPE_CURRENCY))
    {
      count += item->get_quantity();
    }
  }

  return count;
}

uint Inventory::count_currency() const
{
  uint currency_quantity = 0;
  auto raw_items = get_items_cref();

  for (ItemPtr item : raw_items)
  {
    if (item != nullptr && item->get_base_id() == ItemIdKeys::ITEM_ID_CURRENCY)
    {
      currency_quantity += item->get_quantity();
    }
  }

  return currency_quantity;
}

bool Inventory::clear()
{
  items.clear();
  return true;
}

void Inventory::set_additional_property(const string& property_name, const string& property_value)
{
  for (ItemPtr i : items)
  {
    if (i != nullptr)
    {
      i->set_additional_property(property_name, property_value);
    }
  }
}

bool Inventory::has_items() const
{
  return (items.empty() == false);
}

bool Inventory::has_unpaid_items() const
{
  for (ItemPtr i : items)
  {
    if (i && i->get_unpaid())
    {
      return true;
    }
  }

  return false;
}

ItemPtr Inventory::at(const uint index)
{
  ItemPtr selected_item;
  uint cur_index = 0;
  
  if (index < items.size())
  {
    for (ItemPtr item : items)
    {
      if (cur_index == index)
      {
        selected_item = item;
      }
      
      cur_index++;
    }
  }
  
  return selected_item;
}

ItemPtr Inventory::get_from_id(const std::string& id)
{
  ItemPtr selected_item;
  
  for (ItemPtr item : items)
  {
    if (item->get_id() == id)
    {
      selected_item = item;
      break;
    }
  }
  
  return selected_item;
}

vector<ItemPtr> Inventory::get_all_from_base_id(const string& base_id)
{
  vector<ItemPtr> b_items;

  for (ItemPtr item : items)
  {
    if (item->get_base_id() == base_id)
    {
      b_items.push_back(item);
    }
  }

  return b_items;
}

vector<ItemPtr> Inventory::get_all_from_property(const string& item_property)
{
  vector<ItemPtr> p_items;

  for (ItemPtr item : items)
  {
    if (item && item->has_additional_property(item_property))
    {
      p_items.push_back(item);
    }
  }

  return p_items;
}

vector<ItemPtr> Inventory::get_all_from_property(const string& property_name, const string& required_value)
{
  vector<ItemPtr> p_items;

  for (ItemPtr item : items)
  {
    if (item && item->get_additional_property(property_name) == required_value)
    {
      p_items.push_back(item);
    }
  }

  return p_items;
}

ItemPtr Inventory::get_from_base_id(const std::string& base_id)
{
  ItemPtr selected_item;
  
  for (ItemPtr item : items)
  {
    if (item->get_base_id() == base_id)
    {
      selected_item = item;
      break;
    }
  }
  
  return selected_item;
}

vector<ItemPtr> Inventory::get_from_type(const ItemType item_type)
{
  vector<ItemPtr> itype_items;

  for (ItemPtr item : items)
  {
    if (item && item->get_type() == item_type)
    {
      itype_items.push_back(item);
    }
  }

  return itype_items;
}

// Get whether the inventory is empty
bool Inventory::empty() const
{
  return items.empty();
}

uint Inventory::size() const
{
  return items.size();
}

void Inventory::set_items(const list<ItemPtr>& new_items)
{
  items = new_items;
}

void Inventory::add_items(const list<ItemPtr>& new_items)
{
  std::copy(new_items.begin(), new_items.end(), std::back_inserter(items));
}

// Get the actual Items
list<ItemPtr>& Inventory::get_items_ref()
{
  return items;
}

// Get a list useful for iteration, etc., but not updating
// with new items.
const list<ItemPtr>& Inventory::get_items_cref() const
{
  return items;
}

// Check to see if a particular item type exists within the Inventory
bool Inventory::has_item_type(const ItemType type) const
{
  for (ItemPtr item : items)
  {
    if (item && item->get_type() == type)
    {
      return true;
    }
  }
  
  return false;
}

// Does the inventory have at least one item with a given property?
bool Inventory::has_item_with_property(const string& item_property) const
{
  for (ItemPtr item : items)
  {
    if (item && item->has_additional_property(item_property))
    {
      return true;
    }
  }

  return false;
}

// Does the inventory have at least one item with the given ID?
bool Inventory::has_item(const string& base_id) const
{
  for (ItemPtr item : items)
  {
    if (item && item->get_base_id() == base_id)
    {
      return true;
    }
  }

  return false;

}

// How many items in the inventory with the given property?
uint Inventory::count_items_with_property(const string& item_property) const
{
  uint num_items = 0;

  for (ItemPtr item : items)
  {
    if (item && item->has_additional_property(item_property))
    {
      num_items += item->get_quantity();
    }
  }

  return num_items;
}

uint Inventory::count_items_without_property(const string& item_property) const
{
  uint num_items = 0;

  for (ItemPtr item : items)
  {
    if (item && !item->has_additional_property(item_property))
    {
      num_items += item->get_quantity();
    }
  }

  return num_items;
}

uint Inventory::count_items(const string& item_base_id) const
{
  uint num_items = 0;

  for (ItemPtr item : items)
  {
    if (item && item->get_base_id() == item_base_id)
    {
      num_items += item->get_quantity();
    }
  }

  return num_items;
}

string Inventory::get_drop_effect_sid() const
{
  return "";
}

bool Inventory::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, items.size());

  for (ItemPtr item : items)
  {
    if (item)
    {
      Serialize::write_class_id(stream, item->get_class_identifier());
      item->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
  }

  Serialize::write_bool(stream, restack);

  return true;
}

// Assumes the class ID has already been read.
bool Inventory::deserialize(istream& stream)
{
  size_t items_size = 0;
  Serialize::read_size_t(stream, items_size);

  items.clear();

  for (unsigned int i = 0; i < items_size; i++)
  {
    ClassIdentifier item_clid = ClassIdentifier::CLASS_ID_NULL;
    Serialize::read_class_id(stream, item_clid);

    if (item_clid != ClassIdentifier::CLASS_ID_NULL)
    {
      ItemPtr item = ItemSerializationFactory::create_item(item_clid);
      if (!item) return false;
      if (!item->deserialize(stream)) return false;

      items.push_back(item);
    }
  }

  Serialize::read_bool(stream, restack);

  return true;
}

ClassIdentifier Inventory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_INVENTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Inventory_test.cpp"
#endif

