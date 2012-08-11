#pragma once
#include <vector>
#include "Tile.hpp"

class TileDescription
{
  public:
    std::string describe(TilePtr tile, bool tile_is_in_fov);
    
  protected:
    std::string format(const std::vector<std::string>& tile_info_strings);
};
