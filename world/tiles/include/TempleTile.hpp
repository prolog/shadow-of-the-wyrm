#pragma once
#include "WorldMapTile.hpp"

class TempleTile : public WorldMapLandmarkTile
{
  public:
    TileType get_tile_type() const;

    std::string get_tile_description_sid() const;
};
