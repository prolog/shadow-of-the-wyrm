#pragma once
#include <vector>
#include "Tile.hpp"

class TileDescription
{
  public:
    TileDescription(const bool tile, const bool feature, const bool creature, const bool items);
    
    std::string describe(TilePtr tile, bool tile_is_in_fov);
    
  protected:
    std::string format(const std::vector<std::string>& tile_info_strings);

    bool show_tile;
    bool show_feature;
    bool show_creature;
    bool show_items;
};
