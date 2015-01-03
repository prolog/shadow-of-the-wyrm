#include "MapExit.hpp"
#include "Serialize.hpp"

using namespace std;

MapExit::MapExit()
: terrain_type(TileType::TILE_TYPE_UNDEFINED)
{
}

MapExit::~MapExit()
{
}

bool MapExit::operator==(const MapExit& me) const
{
  bool result = true;

  result = result && (map_id == me.map_id);
  result = result && (terrain_type == me.terrain_type);

  return result;
}

void MapExit::set_map_id(const string& new_map_id)
{
  map_id = new_map_id;
}

string MapExit::get_map_id() const
{
  return map_id;
}

void MapExit::set_terrain_type(const TileType new_terrain_type)
{
  terrain_type = new_terrain_type;
}

TileType MapExit::get_terrain_type() const
{
  return terrain_type;
}

bool MapExit::is_using_map_id() const
{
  return (!map_id.empty());
}

bool MapExit::is_using_terrain_type() const
{
  return (!is_using_map_id() && terrain_type != TileType::TILE_TYPE_UNDEFINED);
}

bool MapExit::serialize(ostream& stream) const
{
  Serialize::write_string(stream, map_id);
  Serialize::write_enum(stream, terrain_type);

  return true;
}

bool MapExit::deserialize(istream& stream)
{
  Serialize::read_string(stream, map_id);
  Serialize::read_enum(stream, terrain_type);

  return true;
}

ClassIdentifier MapExit::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAP_EXIT;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapExit_test.cpp"
#endif

