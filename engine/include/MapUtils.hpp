#pragma once
#include "Map.hpp"
#include "Dimensions.hpp"
#include <set>
#include <utility>

//class MapComponents;
typedef std::vector<std::set<Coordinate> > MapComponents;
typedef std::vector<std::set<Coordinate> >::const_iterator MapComponentsItc;
typedef std::set<Coordinate> Component;
typedef std::set<Coordinate>::const_iterator ComponentItc;

class MapUtils
{
  public:
    static std::vector<Coordinate> get_adjacent_map_coordinates(const Dimensions& dim, const int row, const int col);
    static MapComponents get_map_components(MapPtr map, const std::set<TileType>& exclusion_tiles);

  protected:
    static void add_connected_tiles_to_component(MapPtr map, const Coordinate& coord, const Dimensions& dim, const std::set<TileType>& exclusion_tiles, Component* component);
    static bool is_tile_contained_in_an_existing_component(const Coordinate&, const MapComponents& components);
};
