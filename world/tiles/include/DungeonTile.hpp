#pragma once
#include "Tile.hpp"

class DungeonTile : public Tile
{
  public:
    TileType get_tile_type() const;
};

