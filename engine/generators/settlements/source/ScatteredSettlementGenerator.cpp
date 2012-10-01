#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "ScatteredSettlementGenerator.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

ScatteredSettlementGenerator::ScatteredSettlementGenerator(MapPtr new_base_map)
: BaseSettlementGenerator(new_base_map)
{
  initialize();
}

ScatteredSettlementGenerator::ScatteredSettlementGenerator(MapPtr new_base_map, const int new_growth_rate)
: BaseSettlementGenerator(new_base_map, growth_rate)
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
  MapPtr map = boost::make_shared<Map>(*base_map);
  current_buildings.clear();
  
  generate_scattered_settlement(map);

  return map;
}

// Check to see if a building can be placed, by seeing if it violates the minimum
// distance requirement.
bool ScatteredSettlementGenerator::can_building_be_placed(const int row, const int col, const int height, const int width)
{
  bool placement_allowed = true;

  Room cur(-1, col, col+width, row, row+height);
  
  BOOST_FOREACH(Room r, current_buildings)
  {
    Coordinate c1(r.get_centre());
    Coordinate c2(cur.get_centre());
    
    if (MapUtils::tile_distance_using_chebyshev(c1, c2) < min_distance_between_buildings)
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
  Dimensions dim    = map->size();
  int rows          = dim.get_y();
  int cols          = dim.get_x();
  int num_buildings = RNG::range(6, 9);
  int num_attempts  = 100;
  
  int attempts  = 0;
  int buildings = 0;
  int row, col, height, width;
  CardinalDirection door_direction;
  
  while ((buildings < num_buildings) && (attempts < num_attempts))
  {
    // JCD FIXME: DEFINE THESE CONSTANTS IN BASESETTLEMENTGENERATOR AND BE DONE WITH IT!
    height = RNG::range(4, 6);
    width  = RNG::range(5, 7);
    row    = RNG::range(1, rows - height - 2);
    col    = RNG::range(1, cols - width - 2);
    door_direction = static_cast<CardinalDirection>(RNG::range(CARDINAL_DIRECTION_NORTH, CARDINAL_DIRECTION_WEST));
    
    if (can_building_be_placed(row, col, height, width))
    {
      generate_building_if_possible(map, row, row+height, col, col+width, door_direction);
      
      Room room(attempts, col, col+width, row, row+width);
      current_buildings.push_back(room);
      
      buildings++;
    }
    
    attempts++;
  }
}

