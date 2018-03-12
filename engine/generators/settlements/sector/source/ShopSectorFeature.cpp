#include "ShopSectorFeature.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "RNG.hpp"
#include "ShopGenerator.hpp"

using namespace std;

bool ShopSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    CardinalDirection door_dir = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false);
    ShopGenerator sg;

    vector<Building> buildings;
    bool b_gen = SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, 100);

    if (b_gen)
    {
      generated = sg.generate_shop(map, buildings.at(0));
    }
  }

  return generated;
}

