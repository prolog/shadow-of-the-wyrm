#include "WaterInventory.hpp"
#include "ActionTextKeys.hpp"

using namespace std;

AllowsItemsType WaterInventory::get_allows_items() const
{
  return AllowsItemsType::ALLOWS_SOME_ITEMS;
}

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

bool WaterInventory::merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc)
{
  if (item != nullptr && item->get_floats())
  {
    return Inventory::merge_or_add(item, inv_add_loc);
  }

  return false;
}

bool WaterInventory::merge(ItemPtr new_item)
{
  if (new_item != nullptr && new_item->get_floats())
  {
    return Inventory::merge(new_item);
  }

  return false;
}

void WaterInventory::set_items(const list<ItemPtr>& new_items)
{
  this->items.clear();

  add_items(new_items);
}

void WaterInventory::add_items(const list<ItemPtr>& new_items)
{
  list<ItemPtr> safe_to_add;

  for (ItemPtr i : new_items)
  {
    if (i != nullptr && i->get_floats())
    {
      safe_to_add.push_back(i);
    }
  }

  Inventory::add_items(safe_to_add);
}

string WaterInventory::get_drop_effect_sid() const
{
  return ActionTextKeys::ACTION_DROP_WATER;
}

ClassIdentifier WaterInventory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WATER_INVENTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/WaterInventory_test.cpp"
#endif
