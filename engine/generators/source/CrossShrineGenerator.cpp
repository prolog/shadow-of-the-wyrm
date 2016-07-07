#include "CrossShrineGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"

using namespace std;

CrossShrineGenerator::CrossShrineGenerator(MapPtr new_base_map)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_SHRINE), base_map(new_base_map)
{
}

MapPtr CrossShrineGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr CrossShrineGenerator::generate()
{
  MapPtr map = make_shared<Map>(*base_map);

  return map;
}

