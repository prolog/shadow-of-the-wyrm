#include "CryptGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

CryptGenerator::CryptGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_CRYPT)
{
}

MapPtr CryptGenerator::generate(const Dimensions& dim)
{
  MapPtr map = std::make_shared<Map>(dim);
  fill(map, TILE_TYPE_ROCK);
  
  auto coord_pairs = generate_central_crypt(map);
   
  return map;
}

TilePtr CryptGenerator::generate_tile(MapPtr current_map, const int row, const int col)
{
  TilePtr grave_tile = tg.generate(TILE_TYPE_CRYPT);

  return grave_tile;
}

bool CryptGenerator::get_permanence_default() const
{
  return true;
}

// Create the central crypt:
//
// - A long room with an ascending staircase near the end
// - Potentially, sarcophagi throughout.
// - Either:
//     - a central room, or
//     - a long series of triple-doored walls (can't give the player an
//       automatic chokepoint!)
tuple<CardinalDirection, Coordinate, Coordinate> CryptGenerator::generate_central_crypt(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int width = RNG::range(cols / 2, cols - (cols / 5));
  int height = RNG::range(rows / 2, rows - (rows / 5));

  // Centre the crypt on the map.
  int startx = (cols / 2) - (width / 2);
  int endx = startx + width;
  int starty = (rows / 2) - (height / 2);
  int endy = starty + height;

  TilePtr tile;
  for (int y = starty; y < endy; y++)
  {
    for (int x = startx; x < endx; x++)
    {
      tile = tg.generate(TILE_TYPE_DUNGEON);
      map->insert(y, x, tile);
    }
  }

  // Generate the up-staircase.
  CardinalDirection d = static_cast<CardinalDirection>(RNG::range(CARDINAL_DIRECTION_NORTH, CARDINAL_DIRECTION_WEST));
  Coordinate stair_coords(0,0);

  switch (d)
  {
    case CARDINAL_DIRECTION_NORTH:
      stair_coords.first = starty + 1;
      stair_coords.second = (startx + endx) / 2;
      break;
    case CARDINAL_DIRECTION_SOUTH:
      stair_coords.first = endy - 2;
      stair_coords.second = (startx + endx) / 2;
      break;
    case CARDINAL_DIRECTION_EAST:
      stair_coords.first = (starty + endy) / 2;
      stair_coords.second = startx + 1;
      break;
    case CARDINAL_DIRECTION_WEST:
    default:
      stair_coords.first = (starty + endy) / 2;
      stair_coords.second = endx - 2;
      break;
  }

  place_staircase(map, stair_coords.first, stair_coords.second, TILE_TYPE_UP_STAIRCASE, TILE_TYPE_CRYPT, DIRECTION_UP, get_permanence(), true);

  // Return the boundaries of the crypt.
  return make_tuple(CARDINAL_DIRECTION_NORTH, make_pair(starty, startx), make_pair(endy, endx));
}
