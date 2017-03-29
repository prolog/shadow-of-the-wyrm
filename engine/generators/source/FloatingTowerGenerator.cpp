#include "FloatingTowerGenerator.hpp"

FloatingTowerGenerator::FloatingTowerGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_AIR)
{
}

MapPtr FloatingTowerGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_AIR);

  return result_map;
}

