#pragma once
#include "common.hpp"
#include "Directions.hpp"

class BoundingBox
{
  public:
    BoundingBox();
    BoundingBox(const Coordinate& tl, const Coordinate& br);
    bool operator==(const BoundingBox& bb) const;

    // Assumption: this is the "top left" of the bounding box.
    Coordinate get_c1() const;

    // Assumption: this i sthe "bottom right" of the bounding box.
    Coordinate get_c2() const;

  protected:
    Coordinate c1;
    Coordinate c2;
};

