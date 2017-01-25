#include "Shop.hpp"
#include "Serialize.hpp"

using namespace std;

Shop::Shop()
: shop_id(""), shopkeeper_id(""), start({-1,-1}), end({-1,-1}), stocked_item_types({})
{
}

Shop::Shop(const string& new_shop_id, const string& new_shopkeeper_id, const Coordinate& new_start, const Coordinate& new_end, const vector<ItemType>& new_stocked_item_types)
: shop_id(new_shop_id), shopkeeper_id(new_shopkeeper_id), start(new_start), end(new_end), stocked_item_types(new_stocked_item_types)
{
}

bool Shop::operator==(const Shop& s) const
{
  bool result = true;
  
  result = result && shop_id == s.shop_id;
  result = result && shopkeeper_id == s.shopkeeper_id;
  result = result && start == s.start;
  result = result && end == s.end;
  result = result && stocked_item_types == s.stocked_item_types;

  return result;
}

void Shop::set_shop_id(const string& new_shop_id)
{
  shop_id = new_shop_id;
}

string Shop::get_shop_id() const
{
  return shop_id;
}

void Shop::set_shopkeeper_id(const string& new_shopkeeper_id)
{
  shopkeeper_id = new_shopkeeper_id;
}

string Shop::get_shopkeeper_id() const
{
  return shopkeeper_id;
}

void Shop::set_start(const Coordinate& new_start)
{
  start = new_start;
}

Coordinate Shop::get_start() const
{
  return start;
}

void Shop::set_end(const Coordinate& new_end)
{
  end = new_end;
}

Coordinate Shop::get_end() const
{
  return end;
}

void Shop::set_stocked_item_types(const vector<ItemType>& new_stocked_item_types)
{
  stocked_item_types = new_stocked_item_types;
}

vector<ItemType> Shop::get_stocked_item_types() const
{
  return stocked_item_types;
}

ClassIdentifier Shop::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SHOP;
}

bool Shop::serialize(ostream& stream) const
{
  Serialize::write_string(stream, shop_id);
  Serialize::write_string(stream, shopkeeper_id);
  Serialize::write_int(stream, start.first);
  Serialize::write_int(stream, start.second);
  Serialize::write_int(stream, end.first);
  Serialize::write_int(stream, end.second);

  Serialize::write_size_t(stream, stocked_item_types.size());

  for (const ItemType itype : stocked_item_types)
  {
    Serialize::write_enum(stream, itype);
  }

  return true;
}

bool Shop::deserialize(istream& stream)
{
  Serialize::read_string(stream, shop_id);
  Serialize::read_string(stream, shopkeeper_id);
  Serialize::read_int(stream, start.first);
  Serialize::read_int(stream, start.second);
  Serialize::read_int(stream, end.first);
  Serialize::read_int(stream, end.second);

  size_t stocked_sz = 0;
  Serialize::read_size_t(stream, stocked_sz);
  stocked_item_types.clear();

  for (size_t i = 0; i < stocked_sz; i++)
  {
    ItemType itype = ItemType::ITEM_TYPE_NULL;
    Serialize::read_enum(stream, itype);

    stocked_item_types.push_back(itype);
  }

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Shop_test.cpp"
#endif

