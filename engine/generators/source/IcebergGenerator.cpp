#include "IcebergGenerator.hpp"
#include "MapProperties.hpp"

IcebergGenerator::IcebergGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SEA)
{
}

MapPtr IcebergGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_ICE);
  result_map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, std::to_string(false));

  return result_map;
}
