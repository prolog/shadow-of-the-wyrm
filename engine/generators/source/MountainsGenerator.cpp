#include "MountainsGenerator.hpp"

MapPtr MountainsGenerator::generate(const Dimensions& dimensions, const std::string& map_exit_id)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_MOUNTAINS);

  return result_map;
}
