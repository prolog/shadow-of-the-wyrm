#include <boost/make_shared.hpp>
#include "MapExitUtils.hpp"

using boost::make_shared;

MapExitUtils::MapExitUtils()
{
}

MapExitUtils::~MapExitUtils()
{
}

// Add an exit to the map itself
void MapExitUtils::add_exit_to_map(MapPtr map, const std::string& map_exit_id)
{
  MapExitPtr map_exit = make_shared<MapExit>();
  map_exit->set_map_id(map_exit_id);
  map->set_map_exit(map_exit);
}

// Attach an exit to a tile, in a particular direction.
void MapExitUtils::add_exit_to_tile(TilePtr tile, const Direction direction, const std::string& map_exit_id)
{
  if (tile)
  {
    TileExitMap& tile_exit_map = tile->get_tile_exit_map_ref();

    MapExitPtr map_exit = make_shared<MapExit>();
    map_exit->set_map_id(map_exit_id);
    
    tile_exit_map[direction] = map_exit;    
  }
}

