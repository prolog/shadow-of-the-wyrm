#pragma once
#include "WorldMapTile.hpp"

class ShoalsTile : public WorldMapTile
{
  public:
    ShoalsTile();

    TileType get_tile_type() const override;
    TileSuperType get_tile_base_super_type() const override;
    WaterType get_water_type() const override;
    
    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

