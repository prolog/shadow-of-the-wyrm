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
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false, bcf.create_house_features(), bcf.create_house_item_ids());
    SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
  }

  return generated;
}

