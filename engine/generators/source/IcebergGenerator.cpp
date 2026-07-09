#include "IcebergGenerator.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

const int IcebergGenerator::Y_DIVISOR_MIN = 5;
const int IcebergGenerator::Y_DIVISOR_MAX = 10;
const int IcebergGenerator::X_DIVISOR_MIN = 7;
const int IcebergGenerator::X_DIVISOR_MAX = 13;

IcebergGenerator::IcebergGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SEA)
{
}

MapPtr IcebergGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_ICE);
  carve_edges(result_map);

  result_map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, std::to_string(false));

  return result_map;
}

void IcebergGenerator::carve_edges(MapPtr map)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int rows = dim.get_y();
    int cols = dim.get_x();
    int y_divisor = RNG::range(Y_DIVISOR_MIN, Y_DIVISOR_MAX);
    int x_divisor = RNG::range(X_DIVISOR_MIN, X_DIVISOR_MAX);
    int y_range = rows / y_divisor;
    int x_range = cols / x_divisor;

    TileGenerator tg;
    TilePtr tile;

    // Do both above and below the ice
    for (int i = 0; i <= y_range; i++)
    {
      for (int x = 0; x < cols; x++)
      {
        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({i, x}, tile);

        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({ rows - 1 - i, x }, tile);
      }
    }

    // Carve the left and right sides
    for (int i = 0; i < x_range; i++)
    {
      for (int y = 0; y < rows; y++)
      {
        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({ y, i }, tile);

        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({ y, cols - 1 - i }, tile);
      }
    }
  }
}
