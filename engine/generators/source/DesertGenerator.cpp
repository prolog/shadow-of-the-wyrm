#include "DesertGenerator.hpp"

DesertGenerator::DesertGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_DESERT)
{
}

MapPtr DesertGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TileType::TILE_TYPE_DESERT);

  return result_map;
}
