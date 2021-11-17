#include "BuildingConfigFactory.hpp"
#include "HouseSectorFeature.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"

using namespace std;

HouseSectorFeature::HouseSectorFeature()
: growth_rate(100)
{
}

HouseSectorFeature::HouseSectorFeature(const bool ruined)
: growth_rate(100)
{
  if (ruined)
  {
    growth_rate = RNG::range(30, 90);
  }
}

bool HouseSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Building> buildings;
    CardinalDirection door_dir = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
    BuildingConfigFactory bcf;
    vector<ClassIdentifier> cl_ids = bcf.create_house_features();
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
    SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate, false);
  }

  return generated;
}

