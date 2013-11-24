#pragma once
#include "Tile.hpp"

class TreeTile : public Tile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;

    virtual Tile* clone();

  private:
    virtual std::string get_default_tree_tile_description_sid() const;
    ClassIdentifier internal_class_identifier() const override;
};

