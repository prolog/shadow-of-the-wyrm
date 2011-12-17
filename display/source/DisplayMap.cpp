#include "DisplayMap.hpp"

using namespace std;

DisplayMap::DisplayMap()
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

void DisplayMap::set(const Coordinate& key, const DisplayTile& value)
{
  display_map[key] = value;
}

DisplayTile DisplayMap::at(const Coordinate& c) const
{
  DisplayTile tile;

  std::map<Coordinate, DisplayTile>::const_iterator map_it = display_map.find(c);

  if (map_it != display_map.end())
  {
    tile = map_it->second;
  }

  return tile;
}

Dimensions DisplayMap::size() const
{
  return dimensions;
}
