#include "MapExitUtils.hpp"

using namespace std;

MapExitUtils::MapExitUtils()
{
}

MapExitUtils::~MapExitUtils()
{
}

// Add an exit to the map itself
void MapExitUtils::add_exit_to_map(MapPtr map, const string& map_exit_id)
{
  MapExitPtr map_exit = make_shared<MapExit>();
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

    MapExitPtr map_exit = make_shared<MapExit>();
    map_exit->set_terrain_type(tile_type);
    
    add_map_tile_exit(map->get_tile_exits_ref(), direction, c);
    tile_exit_map[direction] = map_exit;
  }
}

// Attach a map exit to a tile, in a particular direction.
void MapExitUtils::add_exit_to_tile(MapPtr map, const Coordinate& c, const Direction direction, const string& map_exit_id)
{
  TilePtr tile = map->at(c);

  if (tile)
  {
    TileExitMap& tile_exit_map = tile->get_tile_exit_map_ref();

    MapExitPtr map_exit = make_shared<MapExit>();
    map_exit->set_map_id(map_exit_id);
    
    add_map_tile_exit(map->get_tile_exits_ref(), direction, c);
    tile_exit_map[direction] = map_exit;    
  }
}

void MapExitUtils::add_map_tile_exit(std::map<Direction, vector<Coordinate>>& map_tile_exits, const Direction d, const Coordinate& c)
{
  auto m_it = map_tile_exits.find(d);

  if (m_it == map_tile_exits.end())
  {
    vector<Coordinate> coords{c};
    map_tile_exits.insert(make_pair(d, coords));
  }
  else
  {
    vector<Coordinate>& coords = m_it->second;

    if (find(coords.begin(), coords.end(), c) == coords.end())
    {
      coords.push_back(c);
    }
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/MapExitUtils_test.cpp"
#endif