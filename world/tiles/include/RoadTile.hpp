#pragma once
#include "Tile.hpp"

class RoadTile : public Tile
{
  public:
    TileType get_tile_type() const;
};

