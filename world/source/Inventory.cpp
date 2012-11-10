#include <boost/foreach.hpp>
#include "Inventory.hpp"
#include "ItemSerializationFactory.hpp"
#include "Serialize.hpp"

using namespace std;

Inventory::Inventory()
{
  items.clear();
}

Inventory::~Inventory()
{
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
  BOOST_FOREACH(ItemPtr inv_item, items)
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

bool Inventory::clear()
{
  items.clear();
  return true;
}

ItemPtr Inventory::at(const uint index)
{
  ItemPtr selected_item;
  uint cur_index = 0;
  
  if (index < items.size())
  {
    BOOST_FOREACH(ItemPtr item, items)
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
  
  BOOST_FOREACH(ItemPtr item, items)
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
  
  BOOST_FOREACH(ItemPtr item, items)
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
list<ItemPtr> Inventory::get_items()
{
  return items;
}

// Get a list useful for iteration, etc., but not updating.
const list<ItemPtr> Inventory::get_items_const() const
{
  return items;
}

// Check to see if a particular item type exists within the Inventory
bool Inventory::has_item_type(const ItemType type) const
{
  BOOST_FOREACH(ItemPtr item, items)
  {
    if (item && item->get_type() == type)
    {
      return true;
    }
  }
  
  return false;
}

bool Inventory::serialize(ostream& stream)
{
  Serialize::write_size_t(stream, items.size());

  BOOST_FOREACH(ItemPtr item, items)
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

