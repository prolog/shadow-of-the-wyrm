#include "MountainsGenerator.hpp"

MountainsGenerator::MountainsGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id)
{
}

MapPtr MountainsGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_MOUNTAINS);

  return result_map;
}
