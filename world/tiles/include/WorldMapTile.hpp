#pragma once
#include "Tile.hpp"

class WorldMapTile : public Tile
{
  public:
    WorldMapTile();
    WorldMapTile(const DigChances& dc);

    virtual bool display_description_on_arrival() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class WorldMapLandmarkTile : public WorldMapTile
{
  public:
    virtual bool display_description_on_arrival() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
