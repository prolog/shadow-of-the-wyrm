#pragma once

#include "common.hpp"
#include "Tile.hpp"
#include "StaircaseTile.hpp"

class TileGenerator
{
  public:
    static TilePtr generate(const TileType& tile_type, const TileType& subtile_type = TILE_TYPE_UNDEFINED, const bool generate_random_items = true);
    static StaircaseTilePtr generate_staircase(const StaircaseType& stairs_type);
};
