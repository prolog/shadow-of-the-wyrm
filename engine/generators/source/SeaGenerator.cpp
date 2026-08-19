#include "CoastlineCalculator.hpp"
#include "SeaGenerator.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"

SeaGenerator::SeaGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SEA)
{
}

MapPtr SeaGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_SEA);
  result_map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, std::to_string(false));

  CoastlineCalculator cc;
  if (RNG::percent_chance(cc.calc_pct_chance_shoals(adjacent_tile_types)))
  {
    // ...
  }

  return result_map;
}
