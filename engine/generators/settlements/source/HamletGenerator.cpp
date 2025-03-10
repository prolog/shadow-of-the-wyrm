#include "BuildingConfigFactory.hpp"
#include "GeneratorUtils.hpp"
#include "HamletGenerator.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "TileGenerator.hpp"

using namespace std;

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

  WALL_TILE_TYPE = TileType::TILE_TYPE_ROCK;

  if (RNG::percent_chance(30))
  {
    WALL_TILE_TYPE = TileType::TILE_TYPE_EARTH;
  }
}

// Generate the farming hamlet.
MapPtr HamletGenerator::generate(const Dimensions& /*dim*/)
{
  MapPtr map = generate();

  if (map != nullptr)
  {
    map->set_allow_creature_updates(false);
  }

  return map;
}

MapPtr HamletGenerator::generate()
{
  MapPtr map = std::make_shared<Map>(*base_map);

  generate_circular_hamlet(map);
  generate_wells(map);
  generate_special_inhabitants(map);

  return map;
}

// Generate a road leading into the hamlet.
void HamletGenerator::generate_road(MapPtr map, const int start_col, const int end_col, const int row, const int increment)
{
  TileGenerator tg;
  int cur_col = start_col;

  int sign_row = RNG::percent_chance(50) && row >= 2 ? row - 1 : row + 1;
  int sign_col = RNG::range(start_col, end_col);

  SettlementGeneratorUtils::place_sign(map, sign_row, sign_col, get_additional_property(TileProperties::TILE_PROPERTY_NAME));

  while (cur_col != end_col)
  {
    TilePtr road_tile = tg.generate(TileType::TILE_TYPE_ROAD);
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
  GeneratorUtils::generate_circle(map, circle_row, circle_col, hamlet_size, TileType::TILE_TYPE_ROAD, true);
  
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
  
  BuildingConfigFactory bcf;
  vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
  BuildingGenerationParameters bgpn(start_row, end_row, start_col, end_col, CardinalDirection::CARDINAL_DIRECTION_SOUTH, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids), WALL_TILE_TYPE);

  if (SettlementGeneratorUtils::generate_building_if_possible(map, bgpn, buildings, growth_rate, true))
  {
    potentially_generate_vegetable_garden(map, start_row, end_row, start_col, end_col, 50);
  }
  
  // South
  height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
  width  = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
  start_row = circle_row + hamlet_size + 1;
  end_row   = circle_row + hamlet_size + 1 + height;
  // start_col, end_col the same for North and South
  
  cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
  BuildingGenerationParameters bgps(start_row, end_row, start_col, end_col, CardinalDirection::CARDINAL_DIRECTION_NORTH, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids), WALL_TILE_TYPE);

  if (SettlementGeneratorUtils::generate_building_if_possible(map, bgps, buildings, growth_rate, true))
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
  
  cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
  BuildingGenerationParameters bgpe(start_row, end_row, start_col, end_col, CardinalDirection::CARDINAL_DIRECTION_WEST, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids), WALL_TILE_TYPE);

  if (SettlementGeneratorUtils::generate_building_if_possible(map, bgpe, buildings, growth_rate, true))
  {
    potentially_generate_vegetable_garden(map, start_row, end_row, start_col, end_col, 50);
  }
  
  // West
  height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
  width  = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
  // start_row, end_row the same for East and West.
  start_col = circle_col - hamlet_size - width - 1;
  end_col   = circle_col - hamlet_size - 1;
  
  cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
  BuildingGenerationParameters bgpw(start_row, end_row, start_col, end_col, CardinalDirection::CARDINAL_DIRECTION_EAST, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids), WALL_TILE_TYPE);

  if (SettlementGeneratorUtils::generate_building_if_possible(map, bgpw, buildings, growth_rate, true))
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

  vector<shared_ptr<SectorFeature>> sfeatures = get_sector_features();

  while ((cur_addl_buildings != additional_buildings) && (attempts < 100))
  {
    int height = RNG::range(BUILDING_HEIGHT_MIN, BUILDING_HEIGHT_MAX);
    int width = RNG::range(BUILDING_WIDTH_MIN, BUILDING_WIDTH_MAX);
    
    int row = RNG::range(0, rows-height-1);
    int col = RNG::range(0, cols-width-1);
    int row_end = row+height;
    int col_end = col+width;

    if (!SettlementGeneratorUtils::does_building_overlap(map, row, row_end, col, col_end, 1))
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
        GeneratorUtils::generate_building(map, row, col, height, width, WALL_TILE_TYPE);
        CardinalDirection cd = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));

        // If the building is beyond the road, use an east/west boundary.
        // Otherwise, it's above or below the road, so use north/south.
        if (col > road_col && col > road_end_col) cd = CardinalDirection::CARDINAL_DIRECTION_WEST;
        else if (col < road_col && col < road_end_col) cd = CardinalDirection::CARDINAL_DIRECTION_EAST;
        else if (row + height < road_row) cd = CardinalDirection::CARDINAL_DIRECTION_SOUTH;
        else cd = CardinalDirection::CARDINAL_DIRECTION_NORTH;

        Coordinate door_coords = SettlementGeneratorUtils::get_door_location(row, row + height - 1, col, col + width - 1, cd);
        GeneratorUtils::generate_door(map, door_coords.first, door_coords.second);
        buildings.push_back({ {row, col}, {row_end, col_end}, door_coords });

        potentially_generate_vegetable_garden(map, row, row + height, col, col + width, 30);

        cur_addl_buildings++;
      }
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
    std::vector<CardinalDirection> vcd{ CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH, CardinalDirection::CARDINAL_DIRECTION_WEST };
    
    std::shuffle(vcd.begin(), vcd.end(), RNG::get_engine());
    
    int garden_height = RNG::range(GARDEN_HEIGHT_MIN, GARDEN_HEIGHT_MAX);
    int garden_width  = RNG::range(GARDEN_WIDTH_MIN, GARDEN_WIDTH_MAX);

    while (!vcd.empty())
    {
      CardinalDirection direction = vcd.back();
      vcd.pop_back();
      
      switch(direction)
      {
        case CardinalDirection::CARDINAL_DIRECTION_NORTH:
          garden_generated = SettlementGeneratorUtils::generate_garden_if_possible(map, GardenType::GARDEN_TYPE_VEGETABLE, start_row - garden_height - 1, start_row - 1, start_col, start_col + garden_width);
          break;
        case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
          garden_generated = SettlementGeneratorUtils::generate_garden_if_possible(map, GardenType::GARDEN_TYPE_VEGETABLE, end_row+1, end_row + garden_height, start_col, start_col + garden_width);
          break;
        case CardinalDirection::CARDINAL_DIRECTION_WEST:
          garden_generated = SettlementGeneratorUtils::generate_garden_if_possible(map, GardenType::GARDEN_TYPE_VEGETABLE, start_row, start_row + garden_height, start_col - 1 - garden_width, start_col - 1);
          break;
        case CardinalDirection::CARDINAL_DIRECTION_EAST:
        default:
          garden_generated = SettlementGeneratorUtils::generate_garden_if_possible(map, GardenType::GARDEN_TYPE_VEGETABLE, start_row, start_row + garden_height, end_col + 1, end_col + 1 + garden_width);
          break;
      }
      
      if (garden_generated)
      {
        // Track the garden so we don't build over it.
        buildings.push_back({ {start_row, start_col}, {end_row, end_col}, {} });
        break;
      }
    }
  }
  
  return garden_generated;
}
