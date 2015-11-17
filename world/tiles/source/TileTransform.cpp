#include "TileTransform.hpp"
#include "Serialize.hpp"

using namespace std;

TileTransform::TileTransform()
: coord{0,0}, tile_type(TileType::TILE_TYPE_UNDEFINED), tile_subtype(TileType::TILE_TYPE_UNDEFINED)
{
}

TileTransform::TileTransform(const Coordinate& new_coord, const TileType new_tt, const TileType new_tst, const map<string, string>& new_props)
: coord(new_coord), tile_type(new_tt), tile_subtype(new_tst), properties(new_props)
{
}

bool TileTransform::operator==(const TileTransform& tt) const
{
  bool result = true;

  result = result && (coord == tt.coord);
  result = result && (tile_type == tt.tile_type);
  result = result && (tile_subtype == tt.tile_subtype);
  result = result && (properties == tt.properties);

  return result;
}

void TileTransform::set_coordinate(const Coordinate& new_coord)
{
  coord = new_coord;
}

Coordinate TileTransform::get_coordinate() const
{
  return coord;
}

void TileTransform::set_tile_type(const TileType new_tile_type)
{
  tile_type = new_tile_type;
}

TileType TileTransform::get_tile_type() const
{
  return tile_type;
}

void TileTransform::set_tile_subtype(const TileType new_tile_subtype)
{
  tile_subtype = new_tile_subtype;
}

TileType TileTransform::get_tile_subtype() const
{
  return tile_subtype;
}

void TileTransform::set_properties(const map<string, string>& new_properties)
{
  properties = new_properties;
}

map<string, string> TileTransform::get_properties() const
{
  return properties;
}

bool TileTransform::serialize(ostream& stream) const
{
  Serialize::write_int(stream, coord.first);
  Serialize::write_int(stream, coord.second);
  Serialize::write_enum(stream, tile_type);
  Serialize::write_enum(stream, tile_subtype);
  Serialize::write_string_map(stream, properties);

  return true;
}

bool TileTransform::deserialize(istream& stream)
{
  Serialize::read_int(stream, coord.first);
  Serialize::read_int(stream, coord.second);
  Serialize::read_enum(stream, tile_type);
  Serialize::read_enum(stream, tile_subtype);
  Serialize::read_string_map(stream, properties);

  return true;
}

ClassIdentifier TileTransform::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TILE_TRANSFORM;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileTransform_test.cpp"
#endif
