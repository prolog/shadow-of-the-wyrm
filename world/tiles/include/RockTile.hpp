#pragma once
#include "Tile.hpp"

class RockTile : public Tile
{
  public:
    TileType get_tile_type() const;
};

