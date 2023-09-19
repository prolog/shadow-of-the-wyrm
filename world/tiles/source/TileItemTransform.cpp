#include "TileItemTransform.hpp"
#include "Serialize.hpp"

using namespace std;

TileItemTransform::TileItemTransform()
: coord{0,0}, item_id(""), min_quantity(0), max_quantity(0)
{
}

TileItemTransform::TileItemTransform(const Coordinate& new_coord, const string& new_item_id, const int new_min_quantity, const int new_max_quantity)
: coord(new_coord), item_id(""), min_quantity(new_min_quantity), max_quantity(new_max_quantity)
{
}

bool TileItemTransform::operator==(const TileItemTransform& tt) const
{
  bool result = true;

  result = result && (coord == tt.coord);
  result = result && (item_id == tt.item_id);
  result = result && (min_quantity == tt.min_quantity);
  result = result && (max_quantity == tt.max_quantity);

  return result;
}

void TileItemTransform::set_coordinate(const Coordinate& new_coord)
{
  coord = new_coord;
}

Coordinate TileItemTransform::get_coordinate() const
{
  return coord;
}

void TileItemTransform::set_item_id(const string& new_item_id)
{
  item_id = new_item_id;
}

string TileItemTransform::get_item_id() const
{
  return item_id;
}

void TileItemTransform::set_min_quantity(const int new_min_quantity)
{
  min_quantity = new_min_quantity;
}

int TileItemTransform::get_min_quantity() const
{
  return min_quantity;
}

void TileItemTransform::set_max_quantity(const int new_max_quantity)
{
  max_quantity = new_max_quantity;
}

int TileItemTransform::get_max_quantity() const
{
  return max_quantity;
}

bool TileItemTransform::serialize(ostream& stream) const
{
  Serialize::write_int(stream, coord.first);
  Serialize::write_int(stream, coord.second);
  Serialize::write_string(stream, item_id);
  Serialize::write_int(stream, min_quantity);
  Serialize::write_int(stream, max_quantity);

  return true;
}

bool TileItemTransform::deserialize(istream& stream)
{
  Serialize::read_int(stream, coord.first);
  Serialize::read_int(stream, coord.second);
  Serialize::read_string(stream, item_id);
  Serialize::read_int(stream, min_quantity);
  Serialize::read_int(stream, max_quantity);

  return true;
}

ClassIdentifier TileItemTransform::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TILE_ITEM_TRANSFORM;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileItemTransform_test.cpp"
#endif
