#include "SeaGenerator.hpp"

SeaGenerator::SeaGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_SEA)
{
}

MapPtr SeaGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_SEA);

  return result_map;
}
