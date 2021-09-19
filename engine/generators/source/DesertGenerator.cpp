#include "DesertGenerator.hpp"
#include "GeneratorUtils.hpp"

DesertGenerator::DesertGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_DESERT)
{
}

MapPtr DesertGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TileType::TILE_TYPE_DESERT);

  GeneratorUtils::generate_bazaar_if_necessary(result_map, get_additional_property(TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR));
  GeneratorUtils::generate_hermitage_if_necessary(result_map, get_additional_property(TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE));

  return result_map;
}
