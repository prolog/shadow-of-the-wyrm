#include "BuildingConfigFactory.hpp"
#include "CoordUtils.hpp"
#include "RNG.hpp"
#include "ScatteredSettlementGenerator.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "TileGenerator.hpp"

using namespace std;

ScatteredSettlementGenerator::ScatteredSettlementGenerator(MapPtr new_base_map)
: BaseSettlementGenerator(new_base_map)
{
  initialize();
}

ScatteredSettlementGenerator::ScatteredSettlementGenerator(MapPtr new_base_map, const int new_growth_rate)
: BaseSettlementGenerator(new_base_map, new_growth_rate)
{
  initialize();
}

void ScatteredSettlementGenerator::initialize()
{
  min_distance_between_buildings = 11;
}

// Generate the scattered settlement
MapPtr ScatteredSettlementGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr ScatteredSettlementGenerator::generate()
{
  MapPtr map = std::make_shared<Map>(*base_map);
  current_buildings.clear();
  
  generate_scattered_settlement(map);
  generate_wells(map);
  generate_special_inhabitants(map);

  SettlementGeneratorUtils::generate_perimeter_sign(map, get_additional_property(TileProperties::TILE_PROPERTY_NAME));

  return map;
}

// Check to see if a building can be placed, by seeing if it violates the minimum
// distance requirement.
bool ScatteredSettlementGenerator::can_building_be_placed(const int row, const int col, const int height, const int width)
{
  bool placement_allowed = true;

  vector<string> no_features;
  Room cur(no_features, -1, col, col+width, row, row+height);
  
  for (const Room& r : current_buildings)
  {
    Coordinate c1(r.get_centre());
    Coordinate c2(cur.get_centre());
    
    if (CoordUtils::chebyshev_distance(c1, c2) < min_distance_between_buildings)
    {
      placement_allowed = false;
      break;
    }
  }
  
  return placement_allowed;
}

// Generate the scattered settlement by trying to place buildings, and
// confirming that they are not less than the minimum distance between
// buildings with all the other buildings generated so far.
void ScatteredSettlementGenerator::generate_scattered_settlement(MapPtr map)
{
  BuildingConfigFactory bcf;
  vector<string> no_features;
  Dimensions dim    = map->size();
  int rows          = dim.get_y();
  int cols          = dim.get_x();
  int num_buildings = RNG::range(6, 9);
  int num_attempts  = 100;

  int attempts  = 0;
  int nbuildings = 0;
  int row, row_end, col, col_end, height, width;
  CardinalDirection door_direction;

  vector<shared_ptr<SectorFeature>> sfeatures = get_sector_features();

  while ((nbuildings < num_buildings) && (attempts < num_attempts))
  {
    // JCD FIXME: DEFINE THESE CONSTANTS IN BASESETTLEMENTGENERATOR AND BE DONE WITH IT!
    height = RNG::range(4, 6);
    width = RNG::range(5, 7);
    row = RNG::range(1, rows - height - 2);
    row_end = row + height;
    col = RNG::range(1, cols - width - 2);
    col_end = col + width;
    door_direction = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));

    if (can_building_be_placed(row, col, height, width))
    {
      if (!sfeatures.empty() && RNG::percent_chance(pct_chance_sector_feature))
      {
        pair<bool, int> result = SettlementGeneratorUtils::generate_sector_feature_if_possible(map, { row, col }, { row_end, col_end }, sfeatures);

        if (result.first)
        {
          sfeatures.erase(sfeatures.begin() + result.second);

          // Keep a phantom building so another building doesn't build over it.
          buildings.push_back({ {row, col}, {row_end, col_end}, {} });
        }
      }
      else
      {
        if (!SettlementGeneratorUtils::does_building_overlap(map, row, row_end, col, col_end, 1))
        {
          vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
          BuildingGenerationParameters bgp(row, row + height, col, col + width, door_direction, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
          SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);

          Room room(no_features, attempts, col, col_end, row, row_end);
          current_buildings.push_back(room);

          nbuildings++;
        }
      }
    }
    
    attempts++;
  }
}

