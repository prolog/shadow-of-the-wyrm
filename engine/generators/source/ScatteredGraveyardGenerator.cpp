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
  int rand;

  for (int row = 2; row < rows-2; row++)
  {
    for (int col = 2; col < cols-2; col++)
    {
      rand = RNG::range(1, 100);

      if (rand < 10)
      {
        TilePtr grave = tg.generate(TILE_TYPE_GRAVE);
        map->insert(row, col, grave);
      }
    }
  }
}

