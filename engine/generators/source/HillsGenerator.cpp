#include "HillsGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::string;

HillsGenerator::HillsGenerator(const string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_HILLS)
{
}

MapPtr HillsGenerator::generate(const Dimensions& dim)
{
  TileGenerator tg;
  MapPtr result_map = std::make_shared<Map>(dim);

  int rows = dim.get_y();
  int cols = dim.get_x();

  TilePtr tile;
  TileType tile_type;
  int rand;

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      rand = RNG::range(1, 100);

      if (rand < 2)
      {
        tile_type = TILE_TYPE_WEEDS;
      }
      else if (rand < 5)
      {
        tile_type = TILE_TYPE_SCRUB;
      }
      else if (rand < 6)
      {
        tile_type = TILE_TYPE_CAIRN;
      }
      else if (rand < 7)
      {
        tile_type = TILE_TYPE_BUSH;
      }
      else
      {
        tile_type = TILE_TYPE_FIELD;
      }

      tile = tg.generate(tile_type);
      result_map->insert(row, col, tile);
    }
  }

  return result_map;
}
