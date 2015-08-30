#pragma once
#include <memory>
#include "StaircaseTile.hpp"

class UpStaircaseTile : public StaircaseTile
{
  public:
    TileType get_tile_type() const override;
    StaircaseType get_staircase_type() const;
    
    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using UpStaircaseTilePtr = std::shared_ptr<UpStaircaseTile>;
