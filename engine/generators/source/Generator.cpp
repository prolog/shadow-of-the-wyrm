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

