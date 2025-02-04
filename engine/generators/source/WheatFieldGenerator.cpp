#include "WheatFieldGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "TileGenerator.hpp"

using namespace std;

WheatFieldGenerator::WheatFieldGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_WHEAT)
{
}

MapPtr WheatFieldGenerator::generate(const Dimensions& dim)
{
  MapPtr result_map = std::make_shared<Map>(dim);

  int rows = dim.get_y();
  int cols = dim.get_x();
  TileType tt;
  TileGenerator tg;

  for (int y = 0; y < rows; y++)
  {
    for (int x = 0; x < cols; x++)
    {
      if (y == 0 || x == 0 || y == rows - 1 || x == cols - 1)
      {
        tt = TileType::TILE_TYPE_FIELD;
      }
      else
      {
        tt = TileType::TILE_TYPE_WHEAT;
      }

      TilePtr tile = tg.generate(tt);
      result_map->insert({ y, x }, tile);
    }
  }

  return result_map;
}
