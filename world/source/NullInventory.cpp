#include "NullInventory.hpp"
#include "ItemSerializationFactory.hpp"
#include "Serialize.hpp"

using namespace std;

bool NullInventory::operator==(const IInventory& inv) const
{
  bool result = true;

  int num_items = inv.get_items_cref().size();
  result = (num_items == 0);

  return result;
}

bool NullInventory::add_front(ItemPtr item)
{
  return false;
}

bool NullInventory::add(ItemPtr item)
{
  return false;
}

void NullInventory::merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc)
{
}

bool NullInventory::merge(ItemPtr item)
{
  return false;
}

bool NullInventory::remove(const string& id)
{
  return false;
}

bool NullInventory::remove_by_base_id(const string& base_id)
{
  return false;
}

bool NullInventory::clear()
{
  return true;
}

bool NullInventory::has_items() const
{
  return false;
}

ItemPtr NullInventory::at(const uint index)
{
  ItemPtr nullp;
  return nullp;
}

ItemPtr NullInventory::get_from_id(const std::string& id)
{
  ItemPtr nullp;
  return nullp;
}

ItemPtr NullInventory::get_from_base_id(const std::string& base_id)
{
  ItemPtr nullp;
  return nullp;
}

bool NullInventory::empty() const
{
  return true;
}

uint NullInventory::size() const
{
  return 0;
}

// JCD FIXME LATER
list<ItemPtr>& NullInventory::get_items_ref()
{
  return items;
}

// JCD FIXME LATER
const list<ItemPtr>& NullInventory::get_items_cref() const
{
  return items;
}

bool NullInventory::has_item_type(const ItemType type) const
{
  return false;
}

bool NullInventory::has_item_with_property(const string& additional_property_name) const
{
  return false;
}

int NullInventory::count_items_with_property(const string& additional_property_name) const
{
  return 0;
}

bool NullInventory::serialize(ostream& stream) const
{
  return true;
}

// Assumes the class ID has already been read.
bool NullInventory::deserialize(istream& stream)
{
  return true;
}

ClassIdentifier NullInventory::internal_class_identifier() const
{
  return CLASS_ID_NULL_INVENTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/NullInventory_test.cpp"
#endif

