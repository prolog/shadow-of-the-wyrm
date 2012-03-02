#include "DesertGenerator.hpp"

MapPtr DesertGenerator::generate(const Dimensions& dimensions, const std::string& map_exit_id)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_DESERT);

  return result_map;
}
