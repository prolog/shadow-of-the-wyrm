#pragma once
#include <set>
#include <map>
#include <vector>
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
    static Coordinate get_new_coordinate(const Coordinate& c, const Direction d, const int offset = 1);

    static int get_perimeter_length(const Coordinate& top_left, const Coordinate& bottom_right);

    // Get the perimeter coordinates of a given rectangle.
    static std::vector<Coordinate> get_perimeter_coordinates(const Coordinate& top_left, const Coordinate& bottom_right);

    // Get coordinates used for a beam.
    // A radius 1 beam: *******
    //
    // A radius 2 beam  *******
    //                  *******
    //                  *******
    //
    static std::vector<Coordinate> get_beam_coordinates(const Coordinate& centre_coord, const Direction d, const uint radius);

    // Get the midway points, given the bounding box.
    static std::map<CardinalDirection, Coordinate> get_midway_coordinates(const Coordinate& top_left, const Coordinate& bottom_right);

    // Get all the coordinates in the given range.
    static std::vector<Coordinate> get_coordinates_in_range(const Coordinate& top_left, const Coordinate& bottom_right, const bool start_row_inclusive = true, const bool start_col_inclusive = true, const bool end_row_inclusive = true, const bool end_col_inclusive = true);
    
    // Get the direction of a move given the start and end coordinates.
    static Direction get_direction(const Coordinate& start_coord, const Coordinate& end_coord);

    // Get all the adjacent coordinates for the current row and column, given the map's dimensions.
    static std::vector<Coordinate> get_adjacent_map_coordinates(const Dimensions& dim, const int row, const int col);

    // Are the two line segments "joinable"?  Two segments are joinable iff
    // there is a coordinate adjacent to both.
    static std::pair<bool, std::vector<Coordinate>> are_segments_joinable(const std::pair<Coordinate, Coordinate>& s1, const std::pair<Coordinate, Coordinate>& s2, const int incr);
    static std::pair<bool, std::vector<Coordinate>> are_coordinates_joinable(const Coordinate& c1, const Coordinate& c2, const int incr);

    // Does the segment seg_1 end before seg_2 begins?
    static bool ends_before(const std::pair<Coordinate, Coordinate>& seg_1, const std::pair<Coordinate, Coordinate>& seg_2);

    // Does the segment seg_1 start after seg_2 ends?
    static bool starts_after(const std::pair<Coordinate, Coordinate>& seg_1, const std::pair<Coordinate, Coordinate>& seg_2);

    // Is the line segment horizontal?
    static bool is_horizontal(const std::pair<Coordinate, Coordinate>& segment);

    // Is the line segment vertical?
    static bool is_vertical(const std::pair<Coordinate, Coordinate>& segment);

    // Convert to a "(y,x)" format string
    static std::string to_string(const Coordinate& c);

  protected:
    CoordUtils();
    ~CoordUtils();
};

