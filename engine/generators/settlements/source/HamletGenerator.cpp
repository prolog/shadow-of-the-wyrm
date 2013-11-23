#include "GeneratorUtils.hpp"
#include "HamletGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

HamletGenerator::HamletGenerator(MapPtr new_base_map)
: BaseSettlementGenerator(new_base_map)
{
  initialize_constants();
}

HamletGenerator::HamletGenerator(MapPtr new_base_map, const int new_growth_rate)
: BaseSettlementGenerator(new_base_map, new_growth_rate)
{
  initialize_constants(); 
}

void HamletGenerator::initialize_constants()
{
  GARDEN_HEIGHT_MIN = 4;
  GARDEN_HEIGHT_MAX = 5;
  GARDEN_WIDTH_MIN = 5;
  GARDEN_WIDTH_MAX = 7;

  BUILDING_HEIGHT_MIN = 4;
  BUILDING_HEIGHT_MAX = 5;
  BUILDING_WIDTH_MIN = 5;
  BUILDING_WIDTH_MAX = 7;
}

// Generate the farming hamlet.
MapPtr HamletGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr HamletGenerator::generate()
{
  MapPtr map = std::make_shared<Map>(*base_map);

  generate_circular_hamlet(map);
  
  return map;
}

// Generate a road leading into the hamlet.
void HamletGenerator::generate_road(MapPtr map, const int start_col, const int end_col, const int row, const int increment)
{
  TileGenerator tg;
  int cur_col = start_col;

  while (cur_col != end_col)
  {
    TilePtr road_tile = tg.generate(TILE_TYPE_ROAD);
    map->insert(row, cur_col, road_tile);
    
    cur_col += increment;
  }
}

// Generate a circular hamlet, placing houses appropriately.
void HamletGenerator::generate_circular_hamlet(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  int hamlet_size = RNG::range(rows/7, rows/5);
  int circle_row = rows / 2;
  int circle_col = RNG::range(2 + hamlet_size, cols - 2 - hamlet_size);
  GeneratorUtils::generate_circle(map, circle_row, circle_col, hamlet_size, TILE_TYPE_ROAD);
  
  // Generate a road east or west depending which is the furthest.
  int road_start_col;
  int road_end_col;
  int increment;
  
  if ((circle_col - hamlet_size - 0) > (cols - (circle_col + hamlet_size)))
  {
    road_start_col = circle_col - hamlet_size;
    road_end_col = 0;
    increment = -1;
  }
  else
  {
    road_start_col = circle_col + hamlet_size;
    road_end_col = cols;
    increment = 1;
  }
  
  generate_road(map, road_start_col, road_end_col, circle_row, increment);
  
  // Try to generate buildings around the circle-road.
  generate_core_hamlet_buildings(map, circle_row, circle_col, hamlet_size);
  
  generate_additional_random_buildings(map, circle_row, road_start_col, road_end_col);
}

// Generate buildings around the circular road, if possible.
void HamletGenerator::generate_core_hamlet_buildings(MapPtr map, const int circle_row, const int circle_col, const int hamlet_size)
{  
  // North
  int height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
  int width  = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
  int start_row = circle_row - hamlet_size - height - 1;
  int end_row   = circle_row - hamlet_size - 1;
  int start_col = circle_col - (width / 2);
  int end_col   = circle_col + (width / 2);
  
  if (generate_building_if_possible(map, start_row, end_row, start_col, end_col, CARDINAL_DIRECTION_SOUTH))
  {
    potentially_generate_vegetable_garden(map, start_row, end_row, start_col, end_col, 50);
  }
  
  // South
  height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
  width  = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
  start_row = circle_row + hamlet_size + 1;
  end_row   = circle_row + hamlet_size + 1 + height;
  // start_col, end_col the same for North and South
  
  if (generate_building_if_possible(map, start_row, end_row, start_col, end_col, CARDINAL_DIRECTION_NORTH))
  {
    potentially_generate_vegetable_garden(map, start_row, end_row, start_col, end_col, 50);
  }
  
  // East
  height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
  width  = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
  start_row = circle_row - (height / 2);
  end_row   = circle_row + (height / 2);
  start_col = circle_col + hamlet_size + 1;
  end_col   = circle_col + hamlet_size + width + 1;
  
  if (generate_building_if_possible(map, start_row, end_row, start_col, end_col, CARDINAL_DIRECTION_WEST))
  {
    potentially_generate_vegetable_garden(map, start_row, end_row, start_col, end_col, 50);
  }
  
  // West
  height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
  width  = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
  // start_row, end_row the same for East and West.
  start_col = circle_col - hamlet_size - width - 1;
  end_col   = circle_col - hamlet_size - 1;
  
  if (generate_building_if_possible(map, start_row, end_row, start_col, end_col, CARDINAL_DIRECTION_EAST))
  {
    potentially_generate_vegetable_garden(map, start_row, end_row, start_col, end_col, 50);
  }
}

// Generate a few additional buildings.  Not many - it is a hamlet.
void HamletGenerator::generate_additional_random_buildings(MapPtr map, const int road_row, const int road_col, const int road_end_col)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  int additional_buildings = RNG::range(3, 5);
  
  int cur_addl_buildings = 0;
  int attempts = 0;
  
  while ((cur_addl_buildings != additional_buildings) && (attempts < 100))
  {
    int height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
    int width = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
    
    int row = RNG::range(0, rows-height-1);
    int col = RNG::range(0, cols-width-1);
    
    if (!does_building_overlap(map, row, row+height, col, col+width))
    {
      GeneratorUtils::generate_building(map, row, col, height, width);
      CardinalDirection cd = static_cast<CardinalDirection>(RNG::range(CARDINAL_DIRECTION_NORTH, CARDINAL_DIRECTION_WEST));
      
      // If the building is beyond the road, use an east/west boundary.
      // Otherwise, it's above or below the road, so use north/south.
      if (col > road_col && col > road_end_col) cd = CARDINAL_DIRECTION_WEST;
      else if (col < road_col && col < road_end_col) cd = CARDINAL_DIRECTION_EAST;
      else if (row + height < road_row) cd = CARDINAL_DIRECTION_SOUTH;
      else cd = CARDINAL_DIRECTION_NORTH;
      
      Coordinate door_coords = get_door_location(row, row+height-1, col, col+width-1, cd);
      GeneratorUtils::generate_door(map, door_coords.first, door_coords.second);
      
      potentially_generate_vegetable_garden(map, row, row+height, col, col+width, 30);
      
      cur_addl_buildings++;
    }
    
    attempts++;
  }
}

// Potentially generate a vegetable garden:
// - Generate a random number in (1, 100) and see if it is less or equal than the given p.
// - If it is, successively try to generate a vegetable garden north, south, east, and
//   west of the building.  If at any time we're successful, do a hard stop, and return true.
// - Return false. 
bool HamletGenerator::potentially_generate_vegetable_garden(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const int probability)
{
  bool garden_generated = false;
  
  if (RNG::percent_chance(probability))
  {
    std::vector<CardinalDirection> vcd;
    
    vcd.push_back(CARDINAL_DIRECTION_EAST);
    vcd.push_back(CARDINAL_DIRECTION_NORTH);
    vcd.push_back(CARDINAL_DIRECTION_SOUTH);
    vcd.push_back(CARDINAL_DIRECTION_WEST);
    
    std::random_shuffle(vcd.begin(), vcd.end());
    
    int garden_height = RNG::range(GARDEN_HEIGHT_MIN, GARDEN_HEIGHT_MAX);
    int garden_width  = RNG::range(GARDEN_WIDTH_MIN, GARDEN_WIDTH_MAX);

    while (!vcd.empty())
    {
      CardinalDirection direction = vcd.back();
      vcd.pop_back();
      
      switch(direction)
      {
        case CARDINAL_DIRECTION_NORTH:
          garden_generated = generate_garden_if_possible(map, GARDEN_TYPE_VEGETABLE, start_row - garden_height - 1, start_row - 1, start_col, start_col + garden_width);
          break;
        case CARDINAL_DIRECTION_SOUTH:
          garden_generated = generate_garden_if_possible(map, GARDEN_TYPE_VEGETABLE, end_row+1, end_row + garden_height, start_col, start_col + garden_width);
          break;
        case CARDINAL_DIRECTION_WEST:
          garden_generated = generate_garden_if_possible(map, GARDEN_TYPE_VEGETABLE, start_row, start_row + garden_height, start_col - 1 - garden_width, start_col - 1);
          break;
        case CARDINAL_DIRECTION_EAST:
        default:
          garden_generated = generate_garden_if_possible(map, GARDEN_TYPE_VEGETABLE, start_row, start_row + garden_height, end_col + 1, end_col + 1 + garden_width);
          break;
      }
      
      if (garden_generated) break;
    }
  }
  
  return garden_generated;
}
