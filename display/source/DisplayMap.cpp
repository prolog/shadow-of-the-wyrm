#include <sstream>
#include "DisplayMap.hpp"
#include "MapUtils.hpp"
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
  display_map[MapUtils::convert_coordinate_to_map_key(c)] = value;
}

// A poem:
//
// const correctness worked for me
// until unordered_map -
// I tried to use operator[],
// but then it broke my ::at.
DisplayTile DisplayMap::at(const Coordinate& c) const
{
  auto d_it = display_map.find(MapUtils::convert_coordinate_to_map_key(c));

  if (d_it != display_map.end())
  {
    return d_it->second;
  }
  else
  {
    DisplayTile dt(' ', static_cast<int>(Colour::COLOUR_BLACK));
    return dt;
  }
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
