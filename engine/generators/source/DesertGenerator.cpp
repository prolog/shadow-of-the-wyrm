#include <boost/make_shared.hpp>
#include "DesertGenerator.hpp"

using boost::make_shared;

DesertGenerator::DesertGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_DESERT)
{
}

MapPtr DesertGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = make_shared<Map>(dimensions);

  fill(result_map, TILE_TYPE_DESERT);

  return result_map;
}
