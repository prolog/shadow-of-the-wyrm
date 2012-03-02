#include "SeaGenerator.hpp"

MapPtr SeaGenerator::generate(const Dimensions& dimensions, const std::string& map_exit_id)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_SEA);

  return result_map;
}
