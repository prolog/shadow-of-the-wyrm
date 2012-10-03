#pragma once
#include "WorldMapTile.hpp"

class ShoalsTile : public WorldMapTile
{
  public:
    TileType get_tile_type() const;
    TileSuperType get_tile_super_type() const;
    
    std::string get_tile_description_sid() const;
};

