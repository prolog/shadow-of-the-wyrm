#pragma once
#include "WorldMapTile.hpp"

class BeachTile : public WorldMapTile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;

    virtual Tile* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};

