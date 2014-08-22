#pragma once
#include "Tile.hpp"

// Additional utilities for Tiles, TileTypes, etc., that don't belong on Tile
// itself.
class TileUtils
{
  public:
    static TileType get_opposite_tile_type(const TileType tt);

  protected:
    TileUtils();
    ~TileUtils();
};

