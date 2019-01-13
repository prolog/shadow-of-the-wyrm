#include "BuildingConfigFactory.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "WorkshopSectorFeature.hpp"

using namespace std;

WorkshopSectorFeature::WorkshopSectorFeature()
: growth_rate(100)
{
}

bool WorkshopSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Building> buildings;
    CardinalDirection door_dir = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
    BuildingConfigFactory bcf;
    vector<ClassIdentifier> cl_ids = bcf.create_workshop_features();
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
    SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
  }

  return generated;
}

