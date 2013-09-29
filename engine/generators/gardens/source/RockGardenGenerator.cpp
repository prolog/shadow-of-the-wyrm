#include "RockGardenGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

RockGardenGenerator::RockGardenGenerator(MapPtr new_base_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width)
: GardenGenerator(new_base_map, map_window_start_row, map_window_start_col, map_window_height, map_window_width)
{
}

void RockGardenGenerator::generate()
{
  TileGenerator tg;

  for (int row = window_start_row; row <= window_start_row + window_height; row++)
  {
    for (int col = window_start_col; col <= window_start_col + window_width; col++)
    {
      // 80% chance of Cairn, 20% chance of field
      TilePtr tile = tg.generate(RNG::percent_chance(80) ? TILE_TYPE_CAIRN : TILE_TYPE_FIELD);

      map->insert(row, col, tile);
    }
  }
}
