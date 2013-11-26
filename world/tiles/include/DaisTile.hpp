#pragma once
#include "Tile.hpp"

// Individual floor tile, raised up.
// Will have a slightly different colour to distinguish it.
class DaisTile : public Tile
{
  public:
    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
