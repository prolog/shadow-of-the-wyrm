#pragma once
#include "WorldMapTile.hpp"

// Individual floor tile
class DungeonTile : public Tile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;
};

// The actual dungeon complex
class DungeonComplexTile : public WorldMapLandmarkTile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;
};
