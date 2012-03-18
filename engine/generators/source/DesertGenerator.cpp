#include "DesertGenerator.hpp"

DesertGenerator::DesertGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id)
{
}

MapPtr DesertGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_DESERT);

  return result_map;
}
