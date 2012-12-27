#pragma once
#include "common.hpp"
#include "Dimensions.hpp"

// Utility functions for dealing with coordinates.
class CoordUtils
{
  public:
    static Coordinate incr(const Coordinate& c, const Dimensions& d);
    static Coordinate end();
    static bool is_end(const Coordinate& c);

  protected:
    CoordUtils();
    ~CoordUtils();
};

