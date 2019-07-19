#include "CityGenerator.hpp"

using namespace std;

CityGenerator::CityGenerator(MapPtr new_base_map)
: BaseSettlementGenerator(new_base_map)
{
  initialize();
}

CityGenerator::CityGenerator(MapPtr new_base_map, const int new_growth_rate)
: BaseSettlementGenerator(new_base_map, growth_rate)
{
  initialize();
}

void CityGenerator::initialize()
{
}

MapPtr CityGenerator::generate(const Dimensions& dim)
{
  MapPtr map = std::make_shared<Map>(*base_map);

  // Crazy code goes here.

  return map;
}

MapPtr CityGenerator::generate()
{
  Dimensions base_dim = base_map->size();
  return generate(base_dim);
}
