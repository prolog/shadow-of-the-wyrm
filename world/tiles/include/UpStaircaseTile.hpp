#pragma once
#include "StaircaseTile.hpp"
#include <boost/shared_ptr.hpp>

class UpStaircaseTile : public StaircaseTile
{
  public:
    TileType get_tile_type() const;
    StaircaseType get_staircase_type() const;
};

typedef boost::shared_ptr<UpStaircaseTile> UpStaircaseTilePtr;
