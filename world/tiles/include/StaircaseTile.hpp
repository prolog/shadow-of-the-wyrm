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
    virtual TileType get_tile_type() const = 0;
    virtual StaircaseType get_staircase_type() const = 0;
    
    virtual bool display_description_on_arrival() const { return true; }
};

typedef boost::shared_ptr<StaircaseTile> StaircaseTilePtr;
