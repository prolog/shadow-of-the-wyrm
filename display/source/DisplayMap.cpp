#include "DisplayMap.hpp"

using namespace std;

DisplayMap::DisplayMap(const int r, const int c)
: rows(r), cols(c)
{
  // Because display maps' sizes are known in advance,
  // reserve the amount for a speed boost.
  display_map.resize(rows * cols);
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
  display_map[c.first * cols + c.second] = value;
}

DisplayTile DisplayMap::at(const Coordinate& c) const
{
  DisplayTile tile;

  return display_map.at(c.first * cols + c.second);
}

Dimensions DisplayMap::size() const
{
  Dimensions d(cols, rows);
  return d;
}
