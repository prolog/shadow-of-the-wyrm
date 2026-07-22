#include "IcebergGenerator.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::pair;
using std::vector;

const int IcebergGenerator::Y_DIVISOR_MIN = 3;
const int IcebergGenerator::Y_DIVISOR_MAX = 6;
const int IcebergGenerator::X_DIVISOR_MIN = 3;
const int IcebergGenerator::X_DIVISOR_MAX = 8;

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
  round_overlay_corners(result_map, y_bounds, x_bounds, TileType::TILE_TYPE_SEA);
  result_map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, std::to_string(false));

  return result_map;
}
