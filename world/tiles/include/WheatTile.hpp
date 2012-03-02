#pragma once
#include "Tile.hpp"

class WheatTile : public Tile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;
};
