#include "OrderedGraveyardGenerator.hpp"

using namespace std;

OrderedGraveyardGenerator::OrderedGraveyardGenerator(const std::string& new_map_exit_id)
: GraveyardGenerator(new_map_exit_id)
{
}

// Add the graves in a neat, orderly manner.
void OrderedGraveyardGenerator::add_graves(MapPtr map)
{
  Dimensions dim = map->size();
  
  int rows = dim.get_y();
  int cols = dim.get_x();

  int start_row = 2;
  int end_row = rows - 3;
  int start_col = 2;
  int end_col = cols - 3;

  add_graves(map, start_row, end_row, start_col, end_col);
}

void OrderedGraveyardGenerator::add_graves(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;
  TilePtr grave;

  for (int row = start_row; row <= end_row; row++)
  {
    for (int col = start_col; col <= end_col; col++)
    {
      if ((col % 5) + (row % 3) == 0)
      {
        grave = tg.generate(TILE_TYPE_GRAVE);
        map->insert(row, col, grave);
      }
    }
  }
}
