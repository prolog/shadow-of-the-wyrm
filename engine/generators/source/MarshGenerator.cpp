#include "AllTiles.hpp"
#include "MarshGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

MarshGenerator::MarshGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_MARSH)
{
}

MapPtr MarshGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TILE_TYPE_MARSH);
  result_map = add_random_trees_bushes_weeds_and_reeds(result_map);

  return result_map;
}

TilePtr MarshGenerator::generate_tile(MapPtr current_map, const int row, const int col)
{
  TilePtr result_tile;

  int rand = RNG::range(1, 100);

  if (rand <= 3)
  {
    result_tile = tg.generate(TILE_TYPE_WEEDS);
  }
  else if (rand <= 4)
  {
    result_tile = tg.generate(TILE_TYPE_BUSH);
  }
  else if (rand <= 10)
  {
    result_tile = tg.generate(TILE_TYPE_TREE);
  }
  else if (rand <= 28)
  {
    result_tile = tg.generate(TILE_TYPE_REEDS);
  }

  return result_tile;
}

MapPtr MarshGenerator::add_random_trees_bushes_weeds_and_reeds(MapPtr map)
{
  MapPtr result_map = std::make_shared<Map>(*map);
  Dimensions d = result_map->size();
  int rows = d.get_y();
  int cols = d.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr tile = generate_tile(result_map, row, col);

      if (tile)
      {
        result_map->insert(row, col, tile);
      }
    }
  }

  return result_map;
}
