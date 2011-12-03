#include "DisplayMap.hpp"

using namespace std;

DisplayMap::DisplayMap()
{
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

Dimensions DisplayMap::get_dimensions() const
{
  return dimensions;
}
