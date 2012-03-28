#include "TileGenerator.hpp"
#include "Generator.hpp"
#include "Map.hpp"

using namespace std;

MapPtr Generator::generate()
{
  Dimensions default_dimensions;
  MapPtr result_map = generate(default_dimensions);

  return result_map;
}

void Generator::fill(const MapPtr map, const TileType& tile_type)
{
  Dimensions dim = map->size();

  int rows = dim.get_y();
  int cols = dim.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr current_tile = TileGenerator::generate(tile_type);
      map->insert(row, col, current_tile);
    }
  }
}

// I was using this sort of thing a lot, so I'm moving it here...
void Generator::generate_building(const MapPtr map, const int start_row, const int start_col, const int height, const int width)
{
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
        current_tile = TileGenerator::generate(TILE_TYPE_ROCK);
      }
      else
      {
        current_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
      }

      map->insert(row, col, current_tile);
    }
  }  
}
