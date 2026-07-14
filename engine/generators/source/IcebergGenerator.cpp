#include "IcebergGenerator.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::vector;

const int IcebergGenerator::Y_DIVISOR_MIN = 5;
const int IcebergGenerator::Y_DIVISOR_MAX = 6;
const int IcebergGenerator::X_DIVISOR_MIN = 7;
const int IcebergGenerator::X_DIVISOR_MAX = 10;

IcebergGenerator::IcebergGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SEA)
{
}

MapPtr IcebergGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions); 
  Dimensions dim = result_map->size();

  int y_divisor = RNG::range(Y_DIVISOR_MIN, Y_DIVISOR_MAX);
  int x_divisor = RNG::range(X_DIVISOR_MIN, X_DIVISOR_MAX);
  int y_bounds = dim.get_y() / y_divisor;
  int x_bounds = dim.get_x() / x_divisor;

  fill_with_overlay(result_map, TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_ICE, y_bounds, x_bounds);
  result_map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, std::to_string(false));

  return result_map;
}

void IcebergGenerator::fill_with_overlay(MapPtr map, const TileType fill_tt, const TileType overlay_tt, const int y_bound, const int x_bound)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int rows = dim.get_y();
    int cols = dim.get_x();

    TileGenerator tg;
    TilePtr tile;
    TileType tt = TileType::TILE_TYPE_UNDEFINED;

    for (int y = 0; y < rows; y++)
    {
      for (int x = 0; x < cols; x++)
      {
        tt = overlay_tt;

        if (y <= y_bound || y >= rows - y_bound || x <= x_bound || x >= cols - x_bound)
        {
          tt = fill_tt;
        }

        tile = tg.generate(tt);
        map->insert({ y, x }, tile);
      }
    }
  }
}

