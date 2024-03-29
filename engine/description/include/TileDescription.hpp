#pragma once
#include <vector>
#include "Tile.hpp"

class TileDescription
{
  public:
    TileDescription(const bool show_dist, const bool tile, const bool feature, const bool creature, const bool items);
    
    std::string describe(CreaturePtr viewing_creature, const Coordinate& source, const Coordinate& dest, TilePtr tile, const bool tile_is_in_fov, const bool is_world_map);
    
  protected:
    std::string format(const std::vector<std::string>& tile_info_strings);

    bool show_distance;
    bool show_tile;
    bool show_feature;
    bool show_creature;
    bool show_items;
};
