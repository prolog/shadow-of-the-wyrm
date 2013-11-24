#pragma once
#include "Tile.hpp"

// Individual floor tile, raised up.
// Will have a slightly different colour to distinguish it.
class DaisTile : public Tile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;

    virtual Tile* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};
