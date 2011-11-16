#pragma once
#include "Tile.hpp"

class FieldTile : public Tile
{
  public:
    TileType get_tile_type() const;
};

