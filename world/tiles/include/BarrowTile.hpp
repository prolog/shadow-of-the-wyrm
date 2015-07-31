#pragma once
#include "Tile.hpp"

class BarrowTile : public Tile
{
  public:
    BarrowTile();
    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

