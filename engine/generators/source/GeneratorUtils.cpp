#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "Log.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

// Hidden away by protected access
GeneratorUtils::GeneratorUtils()
{
}

GeneratorUtils::~GeneratorUtils()
{
}

// Create a circle.  Check to ensure that the radius won't take us off
// the boundaries.
void GeneratorUtils::generate_circle(MapPtr map, const int row_centre, const int col_centre, const int radius, const TileType tile_type)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  if ((position_in_range(0, rows-1, row_centre - radius)) 
   && (position_in_range(0, rows-1, row_centre + radius))
   && (position_in_range(0, cols-1, col_centre - radius))
   && (position_in_range(0, cols+1, col_centre + radius)))
  {
    // Midpoint circle algorithm.  Thank you, internets.
    // (Both of you - you're super.)
    //
    // Really, I wonder how I wrote code when I was a kid,
    // hacking C in djgpp, with no knowledge of data structures
    // and types outside of ints, chars, and arrays.

    // A midpoint circle
    // Math from basic principles:
    // Knowledge gone like ghosts.
    int y0 = row_centre;
    int x0 = col_centre;
    
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    
    generate_tile(map, y0+radius, x0, tile_type);
    generate_tile(map, y0-radius, x0, tile_type);
    generate_tile(map, y0, x0+radius, tile_type);
    generate_tile(map, y0, x0-radius, tile_type);
    
    while (x < y)
    {
      // ddF_x = 2 * x + 1;
      // ddF_y = -2 * y;
      // f == x*x + y*y - radius*radius + 2*x - y+1;
      if (f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_x;
      }
      
      x++;
      ddF_x += 2;
      f += ddF_x;
      
      generate_tile(map, y0 + y, x0 + x, tile_type);
      generate_tile(map, y0 + y, x0 - x, tile_type);
      generate_tile(map, y0 - y, x0 + x, tile_type);
      generate_tile(map, y0 - y, x0 - x, tile_type);
      generate_tile(map, y0 + x, x0 + y, tile_type);
      generate_tile(map, y0 + x, x0 - y, tile_type);
      generate_tile(map, y0 - x, x0 + y, tile_type);
      generate_tile(map, y0 - x, x0 - y, tile_type);
    }
  }
}

bool GeneratorUtils::position_in_range(const int min, const int max, const int actual)
{
  return (actual >= min) && (actual <= max);  
}

// I was using this sort of thing a lot, so I'm moving it here...
void GeneratorUtils::generate_building(const MapPtr map, const int start_row, const int start_col, const int height, const int width)
{
  TileGenerator tg;

  int end_row = start_row + height;
  int end_col = start_col + width;

  TilePtr current_tile;

  for (int row = start_row; row < end_row; row++)
  {
    for (int col = start_col; col < end_col; col++)
    {
      // Generate a wall at the borders, floor otherwise.
      if ((row == start_row) || (row == (end_row - 1))
        ||(col == start_col) || (col == (end_col - 1)))
      {
        current_tile = tg.generate(TILE_TYPE_ROCK);
      }
      else
      {
        current_tile = tg.generate(TILE_TYPE_DUNGEON);
      }

      map->insert(row, col, current_tile);
    }
  }  
}

void GeneratorUtils::generate_door(const MapPtr map, const int row, const int col)
{
  TileGenerator tg;

  TilePtr floor   = tg.generate(TILE_TYPE_DUNGEON);
  FeaturePtr door = FeatureGenerator::generate_door();

  if (floor && map)
  {
    floor->set_feature(door);
    map->insert(row, col, floor);
  }
}

// Generate a tile of a given type at a given location on a given map (that's a given).
void GeneratorUtils::generate_tile(const MapPtr map, const int row, const int col, const TileType tile_type)
{
  TileGenerator tg;
  TilePtr tile = tg.generate(tile_type);
  if (tile && map)
  {
    map->insert(row, col, tile);
  }
}

void GeneratorUtils::generate_fire_pillar(const MapPtr map, const int row, const int col)
{
  FeaturePtr fire_pillar = FeatureGenerator::generate_fire_pillar();
  TilePtr tile = map->at(row, col);
  
  if (tile)
  {
    tile->set_feature(fire_pillar);
  }
}

void GeneratorUtils::generate_fountain(const MapPtr map, const int row, const int col)
{
  FeaturePtr fountain = FeatureGenerator::generate_fountain();
  TilePtr tile = map->at(row, col);
  
  if (tile)
  {
    tile->set_feature(fountain);
  }
}

// Generate a random trap from the list and place it at the given coordinates.
void GeneratorUtils::generate_trap(const MapPtr map, const int row, const int col, const vector<TrapPtr>& traps)
{
  if (!traps.empty())
  {
    size_t trap_size = traps.size();

    uint idx = RNG::range(0, trap_size-1);
    TrapPtr trap = traps.at(idx);

    if (trap != nullptr)
    {
      // Make a copy of the one provided.
      trap = TrapPtr(trap->clone());

      // Set the new copy on to the tile.
      TilePtr tile = map->at(row, col);

      if (tile != nullptr)
      {
        tile->set_feature(trap);

        ostringstream ss;
        ss << "GeneratorUtils::generate_trap - trap generated at (" << row << "," << col << ").";
        Log::instance().debug(ss.str());
      }
    }
  }
}