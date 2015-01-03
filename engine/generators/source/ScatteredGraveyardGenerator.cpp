#include "RNG.hpp"
#include "ScatteredGraveyardGenerator.hpp"
#include "TileGenerator.hpp"

ScatteredGraveyardGenerator::ScatteredGraveyardGenerator(const std::string& new_map_exit_id)
: GraveyardGenerator(new_map_exit_id)
{
}

void ScatteredGraveyardGenerator::add_graves(MapPtr map)
{
  TileGenerator tg;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int start_row = 2;
  int end_row = rows - 3;
  int start_col = 2;
  int end_col = cols - 3;

  add_graves(map, start_row, end_row, start_col, end_col);
}

void ScatteredGraveyardGenerator::add_graves(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  for (int row = start_row; row <= end_row; row++)
  {
    for (int col = start_col; col <= end_col; col++)
    {
      if (RNG::percent_chance(10))
      {
        TilePtr grave = tg.generate(TileType::TILE_TYPE_GRAVE);
        map->insert(row, col, grave);
      }
    }
  }
}