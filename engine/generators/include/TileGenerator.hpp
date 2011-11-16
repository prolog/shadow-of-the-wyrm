#pragma once

#include "common.hpp"
#include "Tile.hpp"
#include "StaircaseTile.hpp"

class TileGenerator
{
  public:
    static TilePtr generate(const TileType& tile_type);
    static StaircaseTilePtr generate_staircase(const StaircaseType& stairs_type);
};
