#include "RectangularShrineGenerator.hpp"

using namespace std;

RectangularShrineGenerator::RectangularShrineGenerator(MapPtr new_base_map)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_SHRINE)
{
}

MapPtr RectangularShrineGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr RectangularShrineGenerator::generate()
{
  MapPtr map = make_shared<Map>(*base_map);

  return map;
}

