#pragma once
#include "Tile.hpp"

class SeabedTile : public Tile
{
  public:
    SeabedTile();

    TileType get_tile_type() const override;
    TileSuperType get_tile_base_super_type() const;
    WaterType get_water_type() const override;
    
    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

