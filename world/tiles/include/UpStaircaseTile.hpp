#pragma once
#include <memory>
#include "StaircaseTile.hpp"

class UpStaircaseTile : public StaircaseTile
{
  public:
    TileType get_tile_type() const;
    StaircaseType get_staircase_type() const;
    
    std::string get_tile_description_sid() const;

    virtual Tile* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<UpStaircaseTile> UpStaircaseTilePtr;
