#include "DesertGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"

DesertGenerator::DesertGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_DESERT)
{
}

MapPtr DesertGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TileType::TILE_TYPE_DESERT);

  if (RNG::percent_chance(5))
  {
    GeneratorUtils::add_random_springs(result_map);
  }

  GeneratorUtils::potentially_generate_coastline(result_map, this);

  return result_map;
}
