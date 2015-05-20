#include "MotteBaileyCastleGeneratorStrategy.hpp"
#include "CoordUtils.hpp"
#include "DirectionUtils.hpp"
#include "GeneratorUtils.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

const int MotteBaileyCastleGeneratorStrategy::MIN_MOTTE_WIDTH = 8;
const int MotteBaileyCastleGeneratorStrategy::MIN_MOTTE_HEIGHT = 6;

// The motte is the keep, bailey is the courtyard.
void MotteBaileyCastleGeneratorStrategy::generate(MapPtr castle_map)
{
  Dimensions d;
  int moat_radius = RNG::range(d.get_y()/2 - 3, d.get_y()/2 - 2);
  int start_y = RNG::range(2, d.get_y() / 4);
  int start_x = RNG::range(5, d.get_x() / 4);
  int end_y = d.get_y() - start_y;
  int end_x = d.get_x() - start_x;
  int motte_width = RNG::range(MIN_MOTTE_WIDTH, end_x - start_x - 4);
  int motte_height = RNG::range(MIN_MOTTE_HEIGHT, end_y - start_y - 4);

  generate_moat(castle_map, start_y, start_x, end_y, end_x);
  generate_motte(castle_map, motte_height, motte_width);
  generate_bridge(castle_map, start_y, start_x, end_y, end_x);
}

// Generate the moat around the castle structure, generated on the
// centre of the map.
void MotteBaileyCastleGeneratorStrategy::generate_moat(MapPtr castle_map, const int start_y, const int start_x, int end_y, int end_x)
{
  TileGenerator tg;
  Dimensions dim = castle_map->size();
  vector<Coordinate> coords = CoordUtils::get_perimeter_coordinates(make_pair(start_y, start_x), make_pair(end_y, end_x));

  for (const Coordinate& c : coords)
  {
    TilePtr river_tile = tg.generate(TileType::TILE_TYPE_RIVER);
    castle_map->insert(c.first, c.second, river_tile);
  }
}

// Generate the motte (the keep).
void MotteBaileyCastleGeneratorStrategy::generate_motte(MapPtr castle_map, const int motte_height, const int motte_width)
{
  Dimensions dim = castle_map->size();
  int start_row = (dim.get_y() / 2) - (motte_height / 2);
  int start_col = (dim.get_x() / 2) - (motte_width / 2);

  Coordinate top_left = make_pair(start_row, start_col);
  Coordinate bottom_right = make_pair(start_row + motte_height, start_col + motte_width);

  GeneratorUtils::generate_building(castle_map, start_row, start_col, motte_height+1, motte_width+1);
  map<CardinalDirection, Coordinate> midway_points = CoordUtils::get_midway_coordinates(top_left, bottom_right);

  for (const auto& c : midway_points)
  {
    GeneratorUtils::generate_door(castle_map, c.second.first, c.second.second);
  }
}

// Generate a land bridge over the moat.
void MotteBaileyCastleGeneratorStrategy::generate_bridge(MapPtr castle_map, const int start_y, const int start_x, const int end_y, const int end_x)
{
  CardinalDirection cd = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
  Coordinate a = make_pair(start_y, start_x);
  Coordinate b = make_pair(end_y, end_x);
  map<CardinalDirection, Coordinate> bridge_coords = CoordUtils::get_midway_coordinates(a, b);

  auto b_it = bridge_coords.begin();
  std::advance(b_it, RNG::range(0, bridge_coords.size() - 1));

  Coordinate c = b_it->second;
  TilePtr bridge_tile = castle_map->at(c);
  TileGenerator tg;

  if (bridge_tile != nullptr)
  {
    bridge_tile = tg.generate(TileType::TILE_TYPE_ROAD);
    castle_map->insert(c.first, c.second, bridge_tile);
  }
}