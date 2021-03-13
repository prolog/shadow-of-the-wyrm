#include "WaterInventory.hpp"

using namespace std;

bool WaterInventory::add_front(ItemPtr new_item)
{
  if (new_item != nullptr && new_item->get_floats())
  {
    return Inventory::add_front(new_item);
  }

  return false;
}

bool WaterInventory::add(ItemPtr new_item)
{
  if (new_item != nullptr && new_item->get_floats())
  {
    return Inventory::add(new_item);
  }

  return false;
}

void WaterInventory::merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc)
{
  if (item != nullptr && item->get_floats())
  {
    return Inventory::merge_or_add(item, inv_add_loc);
  }
}

bool WaterInventory::merge(ItemPtr new_item)
{
  if (new_item != nullptr && new_item->get_floats())
  {
    return Inventory::merge(new_item);
  }

  return false;
}

void WaterInventory::set_items(const list<ItemPtr>& items)
{
  this->items.clear();

  add_items(items);
}

void WaterInventory::add_items(const list<ItemPtr>& items)
{
  list<ItemPtr> safe_to_add;

  for (ItemPtr i : items)
  {
    if (i != nullptr && i->get_floats())
    {
      safe_to_add.push_back(i);
    }
  }

  Inventory::add_items(safe_to_add);
}

ClassIdentifier WaterInventory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WATER_INVENTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/WaterInventory_test.cpp"
#endif
