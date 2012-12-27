#include "CoordUtils.hpp"

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

#ifdef UNIT_TESTS
#include "unit_tests/CoordUtils_test.cpp"
#endif

