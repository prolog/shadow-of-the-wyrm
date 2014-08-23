#pragma once
#include "Map.hpp"

class MapExitUtils
{
  public:
    static void add_exit_to_map(MapPtr map, const std::string& map_exit_id);
    static void add_exit_to_tile(MapPtr map, const Coordinate& c, const Direction direction, const TileType terrain_type);
    static void add_exit_to_tile(MapPtr map, const Coordinate& c, const Direction direction, const std::string& map_exit_id);
    
  protected:
    MapExitUtils();
    ~MapExitUtils();
};
