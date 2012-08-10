#pragma once
#include "Tile.hpp"

class TileDescription
{
  public:
    std::string describe(TilePtr tile, bool tile_is_in_fov);
};
