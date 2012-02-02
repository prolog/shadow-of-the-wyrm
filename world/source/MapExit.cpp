#include "MapExit.hpp"

using std::string;

MapExit::MapExit()
: terrain_type(TILE_TYPE_UNDEFINED)
{
}

MapExit::~MapExit()
{
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
  return (terrain_type != TILE_TYPE_UNDEFINED);
}
