#pragma once
#include "WorldMapTile.hpp"

class MarshTile : public WorldMapTile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;
    
    int get_movement_multiplier() const;
};

