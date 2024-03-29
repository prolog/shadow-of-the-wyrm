#pragma once
#include "Tile.hpp"
#include <memory>

enum struct StaircaseType
{
  STAIRCASE_UP = 0,
  STAIRCASE_DOWN = 1
};

class StaircaseTile : public Tile
{
  public:
    virtual TileType get_tile_type() const override = 0;
    virtual StaircaseType get_staircase_type() const = 0;
    
    virtual bool display_description_on_arrival() const override { return true; }
    bool is_interior() const override { return true; }

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using StaircaseTilePtr = std::shared_ptr<StaircaseTile>;
