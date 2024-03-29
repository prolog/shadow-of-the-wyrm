#pragma once
#include "Tile.hpp"

// Individual floor tile
class DungeonTile : public Tile
{
  public:
    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;
    bool is_interior() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
