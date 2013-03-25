#include <sstream>
#include "DisplayMap.hpp"

using namespace std;

DisplayMap::DisplayMap(const int r, const int c)
: rows(r), cols(c)
{
  // Because display maps' sizes are known in advance,
  // reserve the amount for a speed boost.
 // display_map.resize(rows * cols);
}

DisplayMap::DisplayMap()
: rows(0), cols(0)
{
}

void DisplayMap::set_cursor_coordinate(const Coordinate& new_cursor_coordinate)
{
  cursor_coordinate = new_cursor_coordinate;
}

Coordinate DisplayMap::get_cursor_coordinate() const
{
  return cursor_coordinate;
}

void DisplayMap::set(const Coordinate& c, const DisplayTile& value)
{
  display_map[c] = value;
}

// A poem:
//
// const correctness worked for me
// until unordered_map -
// I tried to use operator[],
// but then it broke my ::at.
DisplayTile DisplayMap::at(const Coordinate& c) const
{
  return display_map.find(c)->second;
}

Dimensions DisplayMap::size() const
{
  Dimensions d(cols, rows);
  return d;
}

DisplayMapType DisplayMap::get_tiles() const
{
  return display_map;
}
