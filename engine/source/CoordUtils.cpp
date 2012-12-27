#include "CoordUtils.hpp"
#include "MapUtils.hpp"

CoordUtils::CoordUtils()
{
}

CoordUtils::~CoordUtils()
{
}

Coordinate CoordUtils::incr(const Coordinate& c, const Dimensions& d)
{
  Coordinate result = c;

  int rows = d.get_y();
  int cols = d.get_x();

  // First, increment the column.  If it's greater than the max cols,
  // increment the rows.
  if (++result.second >= cols)
  {
    result.second = 0;
    result.first++;
  }

  if (result.first >= rows)
  {
    // If we've gone off the end, set it to the end coordinate.
    return end();
  }

  // It's a valid coordinate, given the current dimensions - return it.
  return result;
}

// Generate the "end" coordinate.
Coordinate CoordUtils::end()
{
  Coordinate end_coord(-1, -1);
  return end_coord;
}

// Check to see if a coordinate is an "end" coordinate.  Similar to the
// idea from STL containers, and "end" coordinate indicates we've gone
// beyond the incrementable range.
bool CoordUtils::is_end(const Coordinate& c)
{
  return (c.first == -1 && c.second == -1);
}

// Check for adjacency - distance must be 1 using the Chessboard distance (Chebyshev).
bool CoordUtils::are_coordinates_adjacent(const Coordinate& c1, const Coordinate& c2)
{
  return (CoordUtils::chebyshev_distance(c1, c2) == 1);
}

// Get the distance between two coordinates using Chebyshev distance
int CoordUtils::chebyshev_distance(Coordinate c1, Coordinate c2)
{
  return std::max(abs(c1.second - c2.second), abs(c1.first - c2.first));
}

// Check to see if movement in a given direction is valid.
bool CoordUtils::is_valid_move(const Dimensions& dim, const Coordinate& c, const Direction d)
{
  bool valid_move = true;

  int max_row = dim.get_y();
  int max_col = dim.get_x();

  Coordinate new_coord = get_new_coordinate(c, d);
  int new_row = new_coord.first;
  int new_col = new_coord.second;

  if (new_row < 0 || new_row >= max_row || new_col < 0 || new_col >= max_col)
  {
    valid_move = false;
  }

  return valid_move;
}

// Generate the next coordinate in a given direction.  Does not do correctness checking!
Coordinate CoordUtils::get_new_coordinate(const Coordinate& c, const Direction d)
{
  Coordinate new_coord = c;

  switch(d)
  {
    case DIRECTION_NULL:
      new_coord = c;
      break;
    case DIRECTION_SOUTH_WEST:
      new_coord.first++;
      new_coord.second--;
      break;
    case DIRECTION_SOUTH:
      new_coord.first++;
      break;
    case DIRECTION_SOUTH_EAST:
      new_coord.first++;
      new_coord.second++;
      break;
    case DIRECTION_WEST:
      new_coord.second--;
      break;
    case DIRECTION_EAST:
      new_coord.second++;
      break;
    case DIRECTION_NORTH_WEST:
      new_coord.first--;
      new_coord.second--;
      break;
    case DIRECTION_NORTH:
      new_coord.first--;
      break;
    case DIRECTION_NORTH_EAST:
      new_coord.first--;
      new_coord.second++;
      break;
    case DIRECTION_UP:
    case DIRECTION_DOWN:
    default:
      break;
  }

  return new_coord;
}

#ifdef UNIT_TESTS
#include "unit_tests/CoordUtils_test.cpp"
#endif

