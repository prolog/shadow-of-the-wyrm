#include "TileTransform.hpp"
#include "Serialize.hpp"

using namespace std;

TileTransform::TileTransform()
: min_transform_time(0), tile_type(TileType::TILE_TYPE_UNDEFINED), tile_subtype(TileType::TILE_TYPE_UNDEFINED)
{
}

TileTransform::TileTransform(const double new_min_time, const TileType new_tt, const TileType new_tst, const map<string, string>& new_props)
: min_transform_time(new_min_time), tile_type(new_tt), tile_subtype(new_tst), properties(new_props)
{
}

bool TileTransform::operator==(const TileTransform& tt) const
{
  bool result = true;

  result = result && (min_transform_time == tt.min_transform_time);
  result = result && (tile_type == tt.tile_type);
  result = result && (tile_subtype == tt.tile_subtype);
  result = result && (properties == tt.properties);

  return result;
}

void TileTransform::set_min_transform_time(const double new_transform_time)
{
  min_transform_time = new_transform_time;
}

double TileTransform::get_min_transform_time() const
{
  return min_transform_time;
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
  Serialize::write_double(stream, min_transform_time);
  Serialize::write_enum(stream, tile_type);
  Serialize::write_enum(stream, tile_subtype);
  Serialize::write_string_map(stream, properties);

  return true;
}

bool TileTransform::deserialize(istream& stream)
{
  Serialize::read_double(stream, min_transform_time);
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
