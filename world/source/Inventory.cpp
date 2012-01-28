#include "Inventory.hpp"

using std::list;

Inventory::Inventory()
{
  items.clear();
}

Inventory::~Inventory()
{
}

// Add an item to the Inventory
bool Inventory::add(ItemPtr item)
{
  bool added_item = false;
  
  if (items.size() < items.max_size())
  {
    // JCD FIXME: Eventually, this should be an insert into the correct position.
    items.push_back(item);
    added_item = true;
  }
  
  return added_item;
}

bool Inventory::remove(ItemPtr item)
{
  bool removed_item = false;
  
  if (items.size() > 0)
  {
    // JCD FIXME Implement this.
    removed_item = false;
  }
  
  return removed_item;
}

// Delete an item from the Inventory

// Get the actual Items
list<ItemPtr> Inventory::get_items()
{
  return items;
}
