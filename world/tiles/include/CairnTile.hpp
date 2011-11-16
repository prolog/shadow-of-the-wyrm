#pragma once
#include "Tile.hpp"

class CairnTile : public Tile
{
  public:
    TileType get_tile_type() const;
};
