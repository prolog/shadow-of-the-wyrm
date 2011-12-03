#include "Map.hpp"

using namespace std;

Map::Map(const Map& new_map)
{
  if (this != &new_map)
  {
    Dimensions new_dimensions = new_map.size();
    std::map<std::pair<int, int>, TilePtr > new_tiles = new_map.get_tiles();

    dimensions = new_dimensions;
    tiles = new_tiles;
  }
}

Map::Map(const Dimensions& new_dimensions)
{
  dimensions = new_dimensions;
}

bool Map::insert(int row, int col, TilePtr tile)
{
  pair<int, int> key = make_pair(row, col);

  tiles[key] = tile;
  return true;
}

TilePtr Map::at(int row, int col)
{
  pair<int, int> key = make_pair(row, col);
  return tiles[key];
}

void Map::set_size(const Dimensions& new_dimensions)
{
  dimensions = new_dimensions;
}

Dimensions Map::size() const
{
  return dimensions;
}

std::map<std::pair<int, int>, TilePtr > Map::get_tiles() const
{
  return tiles;
}

void Map::clear_locations()
{
  locations.clear();
}

void Map::add_location(const string& location, const Coordinate& coordinate)
{
  locations.insert(make_pair(location, coordinate));
}

TilePtr Map::get_tile_at_location(const string& location)
{
  TilePtr tile;

  NamedMapLocations::iterator n_it = locations.find(location);

  if (n_it != locations.end())
  {
    Coordinate coord = n_it->second;
    int row = coord.first;
    int col = coord.second;

    tile = at(row, col);
  }

  return tile;
}
