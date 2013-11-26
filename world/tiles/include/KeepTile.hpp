#pragma once
#include "WorldMapTile.hpp"

class KeepTile : public WorldMapLandmarkTile
{
  public:
    TileType get_tile_type() const override;

    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
