#pragma once
#include "common.hpp"
#include "Dimensions.hpp"
#include "Directions.hpp"

// Utility functions for dealing with coordinates.
class CoordUtils
{
  public:
    static Coordinate incr(const Coordinate& c, const Dimensions& d);
    static Coordinate end();
    static bool is_end(const Coordinate& c);
    static bool are_coordinates_adjacent(const Coordinate& c1, const Coordinate& c2);
    static int chebyshev_distance(Coordinate c1, Coordinate c2);

    // Check to see if the direction is a valid move.
    static bool is_valid_move(const Dimensions& dim, const Coordinate& c, const Direction d);
    
    // Get new coordinates.  "is_valid_move" should always be called first!
    static Coordinate get_new_coordinate(const Coordinate& c, const Direction d);

  protected:
    CoordUtils();
    ~CoordUtils();
};

