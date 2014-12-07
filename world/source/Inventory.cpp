#include "Inventory.hpp"
#include "ItemSerializationFactory.hpp"
#include "Serialize.hpp"

using namespace std;

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
  }

  return result;
}

// Add an item to the front of the inventory.  "add" is usually
// used for creatures; "add_front" for tiles, to get stack-like
// behaviour
bool Inventory::add_front(ItemPtr item)
{
  bool added_item = false;
  
  if (items.size() < items.max_size())
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
  
  if (items.size() < items.max_size())
  {
    // JCD FIXME: Eventually, this should be an insert into the correct position.
    // Maybe.
    items.push_back(item);
    added_item = true;
  }
  
  return added_item;
}

void Inventory::merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc)
{
  if (!merge(item))
  {
    switch(inv_add_loc)
    {
      case INVENTORY_ADDITION_FRONT:
        add_front(item);
        break;
      case INVENTORY_ADDITION_BACK:
      default:
        add(item);
        break;
    }
  }
}

bool Inventory::merge(ItemPtr item)
{
  for (ItemPtr inv_item : items)
  {
    if (inv_item && inv_item->matches(item))
    {
      // Pick up the item by adding the picked up item's quantity to the
      // current item's quantity.
      uint quantity = inv_item->get_quantity() + item->get_quantity();
      inv_item->set_quantity(quantity);
      
      // Merged successfully:
      return true;
    }
  }

  return false;
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

bool Inventory::remove_by_base_id(const string& base_id, const int quantity)
{
  int rem_quantity = quantity;

  if (items.size() > 0)
  {
    list<ItemPtr>::iterator item_it = items.begin();

    while (item_it != items.end())
    {
      bool erased = false;

      ItemPtr current_item = *item_it;
      
      if (current_item && (current_item->get_base_id() == base_id))
      {
        int i_quantity = current_item->get_quantity();

        if (i_quantity <= rem_quantity)
        {
          items.erase(item_it++);
          erased = true;
        }
        else
        {
          current_item->set_quantity(i_quantity - rem_quantity);
        }

        rem_quantity -= i_quantity;

        if (rem_quantity <= 0)
        {
          return true;
        }
      }

      if (!erased)
      { 
        item_it++;
      }
    }    
  }

  return false;
}

bool Inventory::clear()
{
  items.clear();
  return true;
}

bool Inventory::has_items() const
{
  return (items.empty() == false);
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

// Get whether the inventory is empty
bool Inventory::empty() const
{
  return items.empty();
}

uint Inventory::size() const
{
  return items.size();
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

// How many items in the inventory with the given property?
int Inventory::count_items_with_property(const string& item_property) const
{
  int num_items = 0;

  for (ItemPtr item : items)
  {
    if (item && item->has_additional_property(item_property))
    {
      num_items += item->get_quantity();
    }
  }

  return num_items;
}

int Inventory::count_items(const string& item_base_id) const
{
  int num_items = 0;

  for (ItemPtr item : items)
  {
    if (item && item->get_base_id() == item_base_id)
    {
      num_items += item->get_quantity();
    }
  }

  return num_items;
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
      Serialize::write_class_id(stream, CLASS_ID_NULL);
    }
  }

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
    ClassIdentifier item_clid = CLASS_ID_NULL;
    Serialize::read_class_id(stream, item_clid);

    if (item_clid != CLASS_ID_NULL)
    {
      ItemPtr item = ItemSerializationFactory::create_item(item_clid);
      if (!item) return false;
      if (!item->deserialize(stream)) return false;

      items.push_back(item);
    }
  }

  return true;
}

ClassIdentifier Inventory::internal_class_identifier() const
{
  return CLASS_ID_INVENTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Inventory_test.cpp"
#endif

