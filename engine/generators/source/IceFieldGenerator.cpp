#include "IceFieldGenerator.hpp"
#include "MapProperties.hpp"

IceFieldGenerator::IceFieldGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_ICE_FIELD)
{
}

MapPtr IceFieldGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_ICE);

  return result_map;
}
