#include "Building.hpp"

using namespace std;

Building::Building(const Coordinate& top_left, const Coordinate& bottom_right, const Coordinate& door_loc)
: start_c(top_left), end_c(bottom_right), door_c(door_loc)
{
}

pair<Coordinate, Coordinate> Building::get_coords() const
{
  return {start_c, end_c};
}

pair<Coordinate, Coordinate> Building::get_interior_coords() const
{
  return {{start_c.first+1, start_c.second+1}, {end_c.first-1, end_c.second-1}};
}

Coordinate Building::get_door_coord() const
{
  return door_c;
}

#ifdef UNIT_TESTS
#include "unit_tests/Building_test.cpp"
#endif

