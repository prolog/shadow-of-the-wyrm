#pragma once
#include <boost/shared_ptr.hpp>
#include "StaircaseTile.hpp"

class DownStaircaseTile : public StaircaseTile
{
  public:
    TileType get_tile_type() const;
    StaircaseType get_staircase_type() const;
    
    std::string get_tile_description_sid() const;

    virtual Tile* clone();

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<DownStaircaseTile> DownStaircaseTilePtr;
