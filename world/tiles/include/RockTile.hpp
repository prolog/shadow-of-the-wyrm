#pragma once
#include "Tile.hpp"

class RockTile : public Tile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;

    int get_movement_multiplier() const;

    virtual Tile* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};

