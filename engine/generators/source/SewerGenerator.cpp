#include "SewerGenerator.hpp"
#include "RNG.hpp"

SewerGenerator::SewerGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SCRUB)
{
}

MapPtr SewerGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  int rows = dimensions.get_y();
  int cols = dimensions.get_x();

  // ...
   
  return result_map;
}

