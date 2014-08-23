#include "MapExitUtils.hpp"

MapExitUtils::MapExitUtils()
{
}

MapExitUtils::~MapExitUtils()
{
}

// Add an exit to the map itself
void MapExitUtils::add_exit_to_map(MapPtr map, const std::string& map_exit_id)
{
  MapExitPtr map_exit = std::make_shared<MapExit>();
  map_exit->set_map_id(map_exit_id);
  map->set_map_exit(map_exit);
}

// Attach a tile-type map exit to a tile, in a particular direction.
void MapExitUtils::add_exit_to_tile(MapPtr map, const Coordinate& c, const Direction direction, const TileType tile_type)
{
  TilePtr tile = map->at(c);

  if (tile)
  {
    TileExitMap& tile_exit_map = tile->get_tile_exit_map_ref();

    MapExitPtr map_exit = std::make_shared<MapExit>();
    map_exit->set_terrain_type(tile_type);
    
    tile_exit_map[direction] = map_exit;    
  }
}

// Attach a map exit to a tile, in a particular direction.
void MapExitUtils::add_exit_to_tile(MapPtr map, const Coordinate& c, const Direction direction, const std::string& map_exit_id)
{
  TilePtr tile = map->at(c);

  if (tile)
  {
    TileExitMap& tile_exit_map = tile->get_tile_exit_map_ref();

    MapExitPtr map_exit = std::make_shared<MapExit>();
    map_exit->set_map_id(map_exit_id);
    
    tile_exit_map[direction] = map_exit;    
  }
}

