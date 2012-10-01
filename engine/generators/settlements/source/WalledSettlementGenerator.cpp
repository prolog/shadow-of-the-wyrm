#include <boost/make_shared.hpp>
#include "WalledSettlementGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

WalledSettlementGenerator::WalledSettlementGenerator(MapPtr new_base_map)
: BaseSettlementGenerator(new_base_map)
{
  initialize();
}

WalledSettlementGenerator::WalledSettlementGenerator(MapPtr new_base_map, const int new_growth_rate)
: BaseSettlementGenerator(new_base_map, new_growth_rate)
{
  initialize();
}

void WalledSettlementGenerator::initialize()
{
  north_wall = 0;
  south_wall = 0;
  east_wall  = 0;
  west_wall  = 0;
  gate_row   = 0;
  gate_col   = 0;
}

MapPtr WalledSettlementGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr WalledSettlementGenerator::generate()
{
  MapPtr map = boost::make_shared<Map>(*base_map);

  generate_walled_settlement(map);

  return map;
}

// Generate the walls of the settlement, and then generate the buildings
// and other things within the walls.
void WalledSettlementGenerator::generate_walled_settlement(MapPtr map)
{
  generate_walls(map);
  generate_gate(map);
  generate_inner_settlement(map);
}

// Generate the walls around the settlement
void WalledSettlementGenerator::generate_walls(MapPtr map)
{
  Dimensions d = map->size();
  int rows = d.get_y();
  int cols = d.get_x();
  
  int wall_offset = RNG::range(2,3);

  north_wall = 0 + wall_offset;
  south_wall = rows - wall_offset;
  west_wall  = 0 + wall_offset;
  east_wall  = cols - wall_offset;
  
  // North, south wall
  TilePtr wall_tile;
  for (int col = west_wall; col <= east_wall; col++)
  {
    wall_tile = TileGenerator::generate(TILE_TYPE_ROCK);
    map->insert(north_wall, col, wall_tile);
    
    wall_tile = TileGenerator::generate(TILE_TYPE_ROCK);
    map->insert(south_wall, col, wall_tile);
  }
    
  // East, west wall
  for (int row = north_wall; row < south_wall; row++)
  {
    wall_tile = TileGenerator::generate(TILE_TYPE_ROCK);
    map->insert(row, east_wall, wall_tile);
    
    wall_tile = TileGenerator::generate(TILE_TYPE_ROCK);
    map->insert(row, west_wall, wall_tile);
  }
}

void WalledSettlementGenerator::generate_gate(MapPtr map)
{
  int rand = RNG::range(CARDINAL_DIRECTION_NORTH, CARDINAL_DIRECTION_SOUTH);
  
  switch(rand)
  {
    case CARDINAL_DIRECTION_WEST:
    case CARDINAL_DIRECTION_NORTH:
      gate_wall = CARDINAL_DIRECTION_NORTH;
      gate_row  = north_wall;
      gate_col  = (east_wall + west_wall) / 2;
      break;
    case CARDINAL_DIRECTION_EAST:
    case CARDINAL_DIRECTION_SOUTH:
      gate_wall = CARDINAL_DIRECTION_SOUTH;
      gate_row  = south_wall;
      gate_col  = (east_wall + west_wall) / 2;
      break;
    default:
      break;
  }
  
  TilePtr tile    = TileGenerator::generate(TILE_TYPE_DUNGEON);
  FeaturePtr gate = FeatureGenerator::generate_gate();
  tile->set_feature(gate);
  map->insert(gate_row, gate_col, tile); 
}

void WalledSettlementGenerator::generate_inner_settlement(MapPtr map)
{
  switch(gate_wall)
  {
    case CARDINAL_DIRECTION_WEST:
    case CARDINAL_DIRECTION_NORTH:
      generate_road_south(map, gate_row+1, gate_col, south_wall - north_wall - 1, growth_rate, 0, false);
      break;
    case CARDINAL_DIRECTION_EAST:
    case CARDINAL_DIRECTION_SOUTH:
      generate_road_north(map, gate_row-1, gate_col, south_wall - north_wall - 1, growth_rate, 0, false);
      break;
    default: 
      break;
  }

  int gap_height = (south_wall - north_wall) / 2;
  int gap_width = (east_wall - west_wall) / 2;
  int cur_attempts = 0;
  int cur_buildings_generated = 0;
  int num_attempts = 200;
  int num_buildings = RNG::range(6, 9);
  int row, col;
  int height, width;
  CardinalDirection dir;
  int offset_extra = 1;
  
  while ((cur_buildings_generated < num_buildings) && (cur_attempts < num_attempts))
  {
    row    = RNG::range(north_wall+2, south_wall-2);
    col    = RNG::range(west_wall+2, east_wall-2);
    height = RNG::range(std::min(5, gap_height), std::min(7, gap_height));
    width  = RNG::range(std::min(5, gap_width), std::min(9, gap_width));
    dir    = static_cast<CardinalDirection>(RNG::range(CARDINAL_DIRECTION_NORTH, CARDINAL_DIRECTION_WEST));
    
    if (!does_building_overlap(map, row, row+height+1, col, col+width+1, offset_extra))
    {
      generate_building_if_possible(map, row, row+height, col, col+width, dir);
      cur_buildings_generated++;
    }

    cur_attempts++;
  }
}
