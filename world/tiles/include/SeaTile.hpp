#pragma once
#include "Tile.hpp"

class SeaTile : public Tile
{
  public:
    TileType get_tile_type() const;
};

