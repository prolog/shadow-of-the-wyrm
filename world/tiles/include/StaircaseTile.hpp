#pragma once
#include "Tile.hpp"
#include <boost/shared_ptr.hpp>

enum StaircaseType
{
  STAIRCASE_UP = 0,
  STAIRCASE_DOWN = 1
};

class StaircaseTile : public Tile
{
  public:
    TileType get_tile_type() const;
    virtual StaircaseType get_staircase_type() const = 0;
};

typedef boost::shared_ptr<StaircaseTile> StaircaseTilePtr;
