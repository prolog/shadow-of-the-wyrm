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

AllowsItemsType NullInventory::get_allows_items() const
{
  return AllowsItemsType::DISALLOWS_ITEMS;
}

void NullInventory::mark_for_restack()
{
}

bool NullInventory::get_marked_for_restack() const
{
  return false;
}

bool NullInventory::add_front(ItemPtr /*item*/)
{
  return false;
}

bool NullInventory::add(ItemPtr /*item*/)
{
  return false;
}

bool NullInventory::merge_or_add(ItemPtr /*item*/, const InventoryAdditionType /*inv_add_loc*/)
{
  return false;
}

bool NullInventory::merge_or_add(IInventoryPtr /*items*/, const InventoryAdditionType /*inv_add_loc*/)
{
  return false;
}

bool NullInventory::merge_or_add(IInventory* /*items*/, const InventoryAdditionType /*inv_add_loc*/)
{
  return false;
}

bool NullInventory::merge(ItemPtr /*item*/)
{
  return false;
}

bool NullInventory::transfer_to(IInventoryPtr /*items*/)
{
  return false;
}

ItemPtr NullInventory::remove_and_return(const string& /*id*/)
{
  ItemPtr item;
  return item;
}

bool NullInventory::remove(const string& /*id*/)
{
  return false;
}

uint NullInventory::count_items() const
{
  return 0;
}

uint NullInventory::count_currency() const
{
  return 0;
}

pair<bool, vector<ItemPtr>> NullInventory::remove_by_base_id(const string& /*base_id*/, const int /*quantity*/, const map<string, string>& /*properties*/)
{
  pair<bool, vector<ItemPtr>> result = { false, {} };
  return result;
}

bool NullInventory::clear()
{
  return true;
}

void NullInventory::set_additional_property(const string& /*p*/, const string& /*v*/)
{
}

bool NullInventory::has_items() const
{
  return false;
}

bool NullInventory::has_unpaid_items() const
{
  return false;
}

bool NullInventory::has_item(const string& /*base_id*/) const
{
  return false;
}

ItemPtr NullInventory::at(const uint /*index*/)
{
  ItemPtr nullp;
  return nullp;
}

ItemPtr NullInventory::get_from_id(const std::string& /*id*/)
{
  ItemPtr nullp;
  return nullp;
}

vector<ItemPtr> NullInventory::get_all_from_base_id(const std::string& /*base_id*/)
{
  return {};
}

vector<ItemPtr> NullInventory::get_all_from_property(const std::string& /*property_name*/)
{
  return {};
}

vector<ItemPtr> NullInventory::get_all_from_property(const std::string& /*property_name*/, const std::string& /*required_value*/)
{
  return {};
}

ItemPtr NullInventory::get_from_base_id(const std::string& /*base_id*/)
{
  ItemPtr nullp;
  return nullp;
}

vector<ItemPtr> NullInventory::get_from_type(const ItemType /*item_type*/)
{
  vector<ItemPtr> no_items;
  return no_items;
}

bool NullInventory::empty() const
{
  return true;
}

uint NullInventory::size() const
{
  return 0;
}

void NullInventory::set_items(const list<ItemPtr>& /*items*/)
{
}

void NullInventory::add_items(const list<ItemPtr>& /*items*/)
{
}

list<ItemPtr>& NullInventory::get_items_ref()
{
  return items;
}

const list<ItemPtr>& NullInventory::get_items_cref() const
{
  return items;
}

bool NullInventory::has_item_type(const ItemType /*type*/) const
{
  return false;
}

bool NullInventory::has_item_with_property(const string& /*additional_property_name*/) const
{
  return false;
}

uint NullInventory::count_items_with_property(const string& /*additional_property_name*/) const
{
  return 0;
}

uint NullInventory::count_items_without_property(const string& /*additional_property_name*/) const
{
  return 0;
}

uint NullInventory::count_items(const string& /*item_base_id*/) const
{
  return 0;
}

string NullInventory::get_drop_effect_sid() const
{
  return "";
}

bool NullInventory::serialize(ostream& /*stream*/) const
{
  return true;
}

// Assumes the class ID has already been read.
bool NullInventory::deserialize(istream& /*stream*/)
{
  return true;
}

ClassIdentifier NullInventory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_NULL_INVENTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/NullInventory_test.cpp"
#endif

