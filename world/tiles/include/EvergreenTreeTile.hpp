#pragma once
#include "TreeTile.hpp"

class EvergreenTreeTile : public TreeTile
{
  public:
    TileType get_tile_type() const;
    
    virtual Tile* clone();

  private:
    virtual std::string get_default_tree_tile_description_sid() const;
    ClassIdentifier internal_class_identifier() const override;
};

