#pragma once
#include "Tile.hpp"

class WorldMapTile : public Tile
{
  public:
    virtual bool display_description_on_arrival() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class WorldMapLandmarkTile : public WorldMapTile
{
  public:
    virtual bool display_description_on_arrival() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};
