#include "WalledSettlementGenerator.hpp"
#include "BuildingConfigFactory.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "DecisionStrategyProperties.hpp"
#include "FeatureGenerator.hpp"
#include "FruitVegetableGardenGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GraveyardSectorFeature.hpp"
#include "ItemGenerationManager.hpp"
#include "LibrarySectorFeature.hpp"
#include "MapUtils.hpp"
#include "ParkSectorFeature.hpp"
#include "EnclosureSectorFeature.hpp"
#include "PlazaSectorFeature.hpp"
#include "RNG.hpp"
#include "RockGardenGenerator.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "ShadeGardenGenerator.hpp"
#include "ShopSectorFeature.hpp"
#include "ShrineSectorFeature.hpp"
#include "StorehouseSectorFeature.hpp"
#include "TavernSectorFeature.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int WalledSettlementGenerator::MAX_NUM_GUARDS = 4;

WalledSettlementGenerator::WalledSettlementGenerator(MapPtr new_base_map)
: BaseSettlementGenerator(new_base_map), wall_tile_type(TileType::TILE_TYPE_ROCK)
{
  initialize();
}

WalledSettlementGenerator::WalledSettlementGenerator(MapPtr new_base_map, const int new_growth_rate)
: BaseSettlementGenerator(new_base_map, new_growth_rate), wall_tile_type(TileType::TILE_TYPE_ROCK)
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

  pct_chance_sector_feature = 25;

  if (RNG::percent_chance(30))
  {
    wall_tile_type = TileType::TILE_TYPE_EARTH;
  }
}

MapPtr WalledSettlementGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr WalledSettlementGenerator::generate()
{
  MapPtr map = std::make_shared<Map>(*base_map);

  generate_walled_settlement(map);
  generate_wells(map);
  generate_special_inhabitants(map);

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
  TileGenerator tg;
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
    wall_tile = tg.generate(wall_tile_type);
    map->insert(north_wall, col, wall_tile);
    
    wall_tile = tg.generate(wall_tile_type);
    map->insert(south_wall, col, wall_tile);
  }
    
  // East, west wall
  for (int row = north_wall; row < south_wall; row++)
  {
    wall_tile = tg.generate(wall_tile_type);
    map->insert(row, east_wall, wall_tile);
    
    wall_tile = tg.generate(wall_tile_type);
    map->insert(row, west_wall, wall_tile);
  }

  generate_barracks(map, north_wall, south_wall, east_wall, west_wall);
}

void WalledSettlementGenerator::generate_barracks(MapPtr map, const int north_wall, const int south_wall, const int east_wall, const int west_wall)
{
  vector<Direction> corner_v = { Direction::DIRECTION_SOUTH_EAST, Direction::DIRECTION_SOUTH_WEST, Direction::DIRECTION_NORTH_EAST, Direction::DIRECTION_NORTH_WEST };
  Direction d = corner_v.at(RNG::range(0, corner_v.size() - 1));
  CardinalDirection door_dir = CardinalDirection::CARDINAL_DIRECTION_SOUTH;

  Coordinate start_barracks = { 0,0 };
  int sz = RNG::range(4, 5);

  switch (d)
  {
    case Direction::DIRECTION_NORTH_EAST:
      start_barracks = { north_wall + 1, east_wall - 1 - sz };
      break;
    case Direction::DIRECTION_NORTH_WEST:
      start_barracks = { north_wall + 1, west_wall + 1 };
      break;
    case Direction::DIRECTION_SOUTH_EAST:
      start_barracks = { south_wall - 1 - sz, east_wall - 1 - sz };
      door_dir = CardinalDirection::CARDINAL_DIRECTION_NORTH;
      break;
    case Direction::DIRECTION_SOUTH_WEST:
      start_barracks = { south_wall - 1 - sz, west_wall + 1 };
      door_dir = CardinalDirection::CARDINAL_DIRECTION_NORTH;
      break;
    default:
      break;
  }
  
  Coordinate end_barracks = { start_barracks.first + sz, start_barracks.second + sz };
  int danger = map->get_danger();
  ItemGenerationConstraints igc;
  igc.set_item_type_restrictions({ ItemType::ITEM_TYPE_WEAPON, ItemType::ITEM_TYPE_AMMUNITION, ItemType::ITEM_TYPE_ARMOUR });
  igc.set_max_danger_level(danger);
  igc.set_min_danger_level(1);

  vector<ClassIdentifier> class_ids = { ClassIdentifier::CLASS_ID_BED, ClassIdentifier::CLASS_ID_TABLE, ClassIdentifier::CLASS_ID_BARREL };
  vector<string> creature_ids;

  int num_guards = RNG::range(1, MAX_NUM_GUARDS);

  for (int i = 0; i < num_guards; i++)
  {
    creature_ids.push_back(CreatureID::CREATURE_ID_GUARD);
  }

  vector<string> item_ids;

  // JCD FIXME: Item IDs
  BuildingGenerationParameters bgp(start_barracks.first, end_barracks.first, start_barracks.second, end_barracks.second, door_dir, false, class_ids, creature_ids, item_ids, TileType::TILE_TYPE_ROCK);
  SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate, false);

  generate_guards(map, north_wall, south_wall, east_wall, west_wall);
}

void WalledSettlementGenerator::generate_guards(MapPtr map, const int north_wall, const int south_wall, const int east_wall, const int west_wall)
{
  int num_guards = RNG::range(2, 6);
  vector<CardinalDirection> dirs = { CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH, CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_WEST };
  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();
  CreatureFactory cf;

  for (int i = 0; i < num_guards; i++)
  {
    CardinalDirection cd = dirs.at(RNG::range(0, dirs.size()-1));
    Coordinate c = CoordUtils::end();

    switch (cd)
    {
      case CardinalDirection::CARDINAL_DIRECTION_NORTH:
        c = { north_wall + 1, RNG::range(west_wall + 1, east_wall - 1) };
        break;
      case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
        c = { south_wall - 1, RNG::range(west_wall + 1, east_wall - 1) };
        break;
      case CardinalDirection::CARDINAL_DIRECTION_WEST:
        c = { RNG::range(north_wall + 1, south_wall - 1), west_wall + 1 };
        break;
      case CardinalDirection::CARDINAL_DIRECTION_EAST:
      default:
        c = { RNG::range(north_wall + 1, south_wall - 1), east_wall - 1 };
        break;
    }

    CreaturePtr creature = cf.create_by_creature_id(am, CreatureID::CREATURE_ID_GUARD, map);
    GameUtils::add_new_creature_to_map(game, creature, map, c);

    TilePtr tile = map->at(c);

    // Wall guards are always sentries.
    if (tile && tile->has_creature())
    {
      CreaturePtr c = tile->get_creature();
      c->get_decision_strategy()->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SENTINEL, to_string(true));
    }
  }
}

void WalledSettlementGenerator::generate_gate(MapPtr map)
{
  TileGenerator tg;
  CardinalDirection rand = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_SOUTH)));
  int sign_row = 0;
  int sign_col = 0;

  switch(rand)
  {
    case CardinalDirection::CARDINAL_DIRECTION_WEST:
    case CardinalDirection::CARDINAL_DIRECTION_NORTH:
      gate_wall = CardinalDirection::CARDINAL_DIRECTION_NORTH;
      gate_row  = north_wall;
      gate_col  = (east_wall + west_wall) / 2;
      sign_row = north_wall - 1;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_EAST:
    case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
      gate_wall = CardinalDirection::CARDINAL_DIRECTION_SOUTH;
      gate_row  = south_wall;
      gate_col  = (east_wall + west_wall) / 2;
      sign_row = south_wall + 1;
      break;
    default:
      break;
  }
  
  sign_col = RNG::percent_chance(50) ? gate_col - 1 : gate_col + 1;

  TilePtr tile    = tg.generate(TileType::TILE_TYPE_DUNGEON);
  FeaturePtr gate = FeatureGenerator::generate_gate();
  tile->set_feature(gate);
  map->insert(gate_row, gate_col, tile); 

  SettlementGeneratorUtils::place_sign(map, sign_row, sign_col, get_additional_property(TileProperties::TILE_PROPERTY_NAME));
}

void WalledSettlementGenerator::generate_inner_settlement(MapPtr map)
{
  switch(gate_wall)
  {
    case CardinalDirection::CARDINAL_DIRECTION_WEST:
    case CardinalDirection::CARDINAL_DIRECTION_NORTH:
      generate_road_south(map, gate_row+1, gate_col, south_wall - north_wall - 1, growth_rate, 0, false);
      break;
    case CardinalDirection::CARDINAL_DIRECTION_EAST:
    case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
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
  int row, col, row_end, col_end;
  int height, width;
  CardinalDirection dir;
  int offset_extra = 1;
  BuildingConfigFactory bcf;
  
  vector<shared_ptr<SectorFeature>> sfeatures = get_sector_features();

  while ((cur_buildings_generated < num_buildings) && (cur_attempts < num_attempts))
  {
    row     = RNG::range(north_wall+2, south_wall-2);
    col     = RNG::range(west_wall+2, east_wall-2);
    height  = RNG::range(std::min(5, gap_height), std::min(7, gap_height));
    width   = RNG::range(std::min(5, gap_width), std::min(9, gap_width));
    row_end = row + height;
    col_end = col + width;
    dir = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
    
    if (!SettlementGeneratorUtils::does_building_overlap(map, row, row+height+1, col, col+width+1, offset_extra))
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
        vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
        BuildingGenerationParameters bgp(row, row_end, col, col_end, dir, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids), TileType::TILE_TYPE_ROCK);

        SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
        cur_buildings_generated++;
      }
    }

    cur_attempts++;
  }
}

vector<shared_ptr<SectorFeature>> WalledSettlementGenerator::get_sector_features()
{
  vector<shared_ptr<SectorFeature>> sfs;
  shared_ptr<SectorFeature> sf;

  sf = std::make_shared<GraveyardSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<OrchardGenerator>();
  sfs.push_back(sf);

  sf = std::make_shared<FruitVegetableGardenGenerator>();
  sfs.push_back(sf);

  sf = std::make_shared<ParkSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<PlazaSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<RockGardenGenerator>();
  sfs.push_back(sf);

  sf = std::make_shared<ShadeGardenGenerator>();
  sfs.push_back(sf);

  sf = std::make_shared<ShopSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<ShrineSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<LibrarySectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<LittleLibrarySectorFeature>(true);
  sfs.push_back(sf);

  sf = std::make_shared<TavernSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<EnclosureSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<StorehouseSectorFeature>();
  sfs.push_back(sf);

  return sfs;
}