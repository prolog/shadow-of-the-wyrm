#include "MotteBaileyCastleGeneratorStrategy.hpp"
#include "DirectionUtils.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"

using namespace std;

const int MotteBaileyCastleGeneratorStrategy::MIN_MOTTE_WIDTH = 8;
const int MotteBaileyCastleGeneratorStrategy::MIN_MOTTE_HEIGHT = 6;

// The motte is the keep, bailey is the courtyard.
void MotteBaileyCastleGeneratorStrategy::generate(MapPtr castle_map)
{
  Dimensions d;
  int moat_radius = RNG::range(d.get_y()/2 - 3, d.get_y()/2 - 2);
  int max_motte_size = moat_radius - 1;
  int motte_width = RNG::range(MIN_MOTTE_WIDTH, max_motte_size);
  int motte_height = RNG::range(MIN_MOTTE_HEIGHT, max_motte_size);

  generate_moat(castle_map, moat_radius);
  generate_motte(castle_map, motte_height, motte_width);
}

// Generate the moat around the castle structure, generated on the
// centre of the map.
void MotteBaileyCastleGeneratorStrategy::generate_moat(MapPtr castle_map, const int moat_radius)
{
  Dimensions dim = castle_map->size();
  GeneratorUtils::generate_circle(castle_map, dim.get_y()/2, dim.get_x()/2, moat_radius, TileType::TILE_TYPE_RIVER);
}

// Generate the motte (the keep).
void MotteBaileyCastleGeneratorStrategy::generate_motte(MapPtr map, const int motte_height, const int motte_width)
{
  Dimensions dim = map->size();
  int start_row = (dim.get_y() / 2) - (motte_height / 2);
  int start_col = (dim.get_x() / 2) - (motte_width / 2);

  GeneratorUtils::generate_building(map, start_row, start_col, motte_height, motte_width);

  // Generate doors on each wall. (N, S, E, W)
  vector<Coordinate> door_coords = { {start_row, start_col + (motte_width/2) }, 
                                     {start_row + motte_height-1, start_col + (motte_width/2)}, 
                                     {start_row + (motte_height/2), start_col + motte_width - 1}, 
                                     {start_row + (motte_height/2), start_col} };
  for (const Coordinate& c : door_coords)
  {
    GeneratorUtils::generate_door(map, c.first, c.second);
  }
}

