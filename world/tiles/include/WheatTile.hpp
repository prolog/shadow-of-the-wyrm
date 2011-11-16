#pragma once
#include "Tile.hpp"

class WheatTile : public Tile
{
  public:
    TileType get_tile_type() const;
};
