#pragma once
#include "Tile.hpp"

class WorldMapTile : public Tile
{
  public:
    WorldMapTile();

    virtual bool display_description_on_arrival() const;
};

class WorldMapLandmarkTile : public WorldMapTile
{
  public:
    WorldMapLandmarkTile();
    
    virtual bool display_description_on_arrival() const;
};
