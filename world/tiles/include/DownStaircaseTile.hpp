#pragma once
#include <memory>
#include "StaircaseTile.hpp"

class DownStaircaseTile : public StaircaseTile
{
  public:
    TileType get_tile_type() const override;
    StaircaseType get_staircase_type() const override;
    
    std::string get_tile_description_sid() const override;
    bool is_interior() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using DownStaircaseTilePtr = std::shared_ptr<DownStaircaseTile>;
