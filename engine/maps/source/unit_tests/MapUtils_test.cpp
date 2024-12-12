#include "gtest/gtest.h"
#include "FieldGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "MobileDecisionStrategy.hpp"
#include "SeaGenerator.hpp"
#include "DirectionLocationTextKeys.hpp"
#include "TileGenerator.hpp"
#include "UnderwaterGenerator.hpp"

TEST(SW_Engine_Maps_MapUtils, does_hostile_creature_exist)
{
  Dimensions dim;
  MapPtr map = std::make_shared<Map>(dim);

  CreaturePtr player = std::make_shared<Creature>();
  player->set_id(CreatureID::CREATURE_ID_PLAYER);

  CreaturePtr c1 = std::make_shared<Creature>();
  DecisionStrategyPtr dec1 = std::make_unique<MobileDecisionStrategy>(nullptr);
  c1->set_decision_strategy(std::move(dec1));
  c1->set_id("c1");

  CreaturePtr c2 = std::make_shared<Creature>();
  DecisionStrategyPtr dec2 = std::make_unique<MobileDecisionStrategy>(nullptr);
  c2->set_decision_strategy(std::move(dec2));
  c2->set_id("c2");

  vector<string> ids = { "c1", "c2" };
  HostilityManager hm;
  hm.set_hostility_to_player(c2);

  EXPECT_FALSE(MapUtils::does_hostile_creature_exist(map, ids, CreatureID::CREATURE_ID_PLAYER));

  map->add_creature(c1);

  EXPECT_FALSE(MapUtils::does_hostile_creature_exist(map, ids, CreatureID::CREATURE_ID_PLAYER));

  map->add_creature(c2);

  EXPECT_TRUE(MapUtils::does_hostile_creature_exist(map, ids, CreatureID::CREATURE_ID_PLAYER));
}

TEST(SW_Engine_Maps_MapUtils, get_dimensions)
{
  // Size = 0 - dimensions should be 0, regardless.
  uint size = 0;
  Dimensions d;
  int max_rows = d.get_y();
  int max_cols = d.get_x();
  
  Coordinate c(0, 0);
  MapPtr original_map = std::make_shared<Map>(d);

  // "1" is the row/col on which the creature currently stands.  This is always visible.
  EXPECT_EQ(1, MapUtils::get_dimensions(original_map, c, size).get_y());
  EXPECT_EQ(1, MapUtils::get_dimensions(original_map, c, size).get_x());
  
  c.first = 5;
  c.second = 5;
  
  EXPECT_EQ(1, MapUtils::get_dimensions(original_map, c, size).get_y());
  EXPECT_EQ(1, MapUtils::get_dimensions(original_map, c, size).get_x());

  // Centre of a map where the size can expand in all directions
  size = 7;
  c.first = 10;
  c.second = 40;

  int expected_size = size+size+1; // +1 is the creature's row.  visibility extends in each direction.
  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_y());
  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_x());

  // Edge cases
  // Size 5, at 0,0
  size = 5;
  c.first = 0;
  c.second = 0;
  
  expected_size = size+1;

  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_y());
  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_x());
  
  // Size 5, at 0, max
  c.first = 0;
  c.second = max_cols-1;

  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_y());
  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_x());

  // Size 5, at max, 0
  c.first = max_rows-1;
  c.second = 0;

  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_y());
  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_x());

  // Size 5, at max, max
  c.first = max_rows-1;
  c.second = max_cols-1;

  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_y());
  EXPECT_EQ(expected_size, MapUtils::get_dimensions(original_map, c, size).get_x());
}

TEST(SW_Engine_Maps_MapUtils, coordinate_within_dimensions)
{
  Dimensions d;
  Coordinate c(-1, -1);

  EXPECT_FALSE(MapUtils::are_coordinates_within_dimensions(c, d));

  c.first = 0;
  
  EXPECT_FALSE(MapUtils::are_coordinates_within_dimensions(c, d));

  c.second = 0;

  EXPECT_TRUE(MapUtils::are_coordinates_within_dimensions(c, d));

  c.first = d.get_y() - 1;
  c.second = d.get_x() - 1;

  EXPECT_TRUE(MapUtils::are_coordinates_within_dimensions(c, d));

  c.first++;

  EXPECT_FALSE(MapUtils::are_coordinates_within_dimensions(c, d));

  c.first--;
  c.second++;

  EXPECT_FALSE(MapUtils::are_coordinates_within_dimensions(c, d));
}

TEST(SW_Engine_Maps_MapUtils, calculate_depth_delta_map)
{
  EXPECT_EQ(1, MapUtils::calculate_depth_delta(nullptr, nullptr, ExitMovementType::EXIT_MOVEMENT_DESCEND));
  EXPECT_EQ(-1, MapUtils::calculate_depth_delta(nullptr, nullptr, ExitMovementType::EXIT_MOVEMENT_ASCEND));

  Dimensions dim;
  MapPtr map = std::make_shared<Map>(dim);

  EXPECT_EQ(1, MapUtils::calculate_depth_delta(map, nullptr, ExitMovementType::EXIT_MOVEMENT_DESCEND));
  EXPECT_EQ(-1, MapUtils::calculate_depth_delta(map, nullptr, ExitMovementType::EXIT_MOVEMENT_ASCEND));

  map->set_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT, "5");

  EXPECT_EQ(5, MapUtils::calculate_depth_delta(map, nullptr, ExitMovementType::EXIT_MOVEMENT_DESCEND));
  EXPECT_EQ(-5, MapUtils::calculate_depth_delta(map, nullptr, ExitMovementType::EXIT_MOVEMENT_ASCEND));
}

TEST(SW_Engine_Maps_MapUtils, calculate_depth_delta_tile)
{
  EXPECT_EQ(1, MapUtils::calculate_depth_delta(nullptr, nullptr, ExitMovementType::EXIT_MOVEMENT_DESCEND));
  EXPECT_EQ(-1, MapUtils::calculate_depth_delta(nullptr, nullptr, ExitMovementType::EXIT_MOVEMENT_ASCEND));

  Dimensions dim;
  TilePtr tile = std::make_shared<FieldTile>();

  EXPECT_EQ(1, MapUtils::calculate_depth_delta(nullptr, tile, ExitMovementType::EXIT_MOVEMENT_DESCEND));
  EXPECT_EQ(-1, MapUtils::calculate_depth_delta(nullptr, tile, ExitMovementType::EXIT_MOVEMENT_ASCEND));

  tile->set_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT, "5");

  EXPECT_EQ(5, MapUtils::calculate_depth_delta(nullptr, tile, ExitMovementType::EXIT_MOVEMENT_DESCEND));
  EXPECT_EQ(-5, MapUtils::calculate_depth_delta(nullptr, tile, ExitMovementType::EXIT_MOVEMENT_ASCEND));
}

TEST(SW_Engine_Maps_MapUtils, should_link_entry_point)
{
  EXPECT_FALSE(MapUtils::should_link_entry_point(MapType::MAP_TYPE_AIR));
  EXPECT_FALSE(MapUtils::should_link_entry_point(MapType::MAP_TYPE_OVERWORLD));
  EXPECT_TRUE(MapUtils::should_link_entry_point(MapType::MAP_TYPE_WORLD));
  EXPECT_FALSE(MapUtils::should_link_entry_point(MapType::MAP_TYPE_UNDERWORLD));
  EXPECT_FALSE(MapUtils::should_link_entry_point(MapType::MAP_TYPE_UNDERWATER));
  EXPECT_FALSE(MapUtils::should_link_entry_point(MapType::MAP_TYPE_COSMOS));
}

TEST(SW_Engine_Maps_MapUtils, does_area_around_tile_contain_staircase)
{
  Dimensions dim;
  MapPtr map = std::make_shared<Map>(dim);
  TileGenerator tg;

  GeneratorUtils::fill(map, make_pair(0,0), make_pair(dim.get_y()-1, dim.get_x()-1), TileType::TILE_TYPE_DUNGEON);

  // Put an up staircase at 4,4 and a down staircase at 15,15
  TilePtr up_staircase = tg.generate_staircase(StaircaseType::STAIRCASE_UP);
  TilePtr down_staircase = tg.generate_staircase(StaircaseType::STAIRCASE_DOWN);

  map->insert(make_pair(4,4), up_staircase);

  EXPECT_TRUE(MapUtils::does_area_around_tile_contain_staircase(map, make_pair(4,5)));
  EXPECT_TRUE(MapUtils::does_area_around_tile_contain_staircase(map, make_pair(5,4)));
  EXPECT_FALSE(MapUtils::does_area_around_tile_contain_staircase(map, make_pair(7,7)));

  map->insert(make_pair(15,15), down_staircase);

  EXPECT_TRUE(MapUtils::does_area_around_tile_contain_staircase(map, make_pair(15,16)));
  EXPECT_TRUE(MapUtils::does_area_around_tile_contain_staircase(map, make_pair(14,15)));
  EXPECT_FALSE(MapUtils::does_area_around_tile_contain_staircase(map, make_pair(10,10)));
}

TEST(SW_Engine_Maps_MapUtils, is_coordinate_within_player_restricted_zone)
{
  Dimensions dim;
  MapPtr map = std::make_shared<Map>(dim);

  GeneratorUtils::fill(map, make_pair(0,0), make_pair(dim.get_y()-1, dim.get_x()-1), TileType::TILE_TYPE_DUNGEON);

  map->add_or_update_location(CreatureID::CREATURE_ID_PLAYER, make_pair(0,0));
  Coordinate c = make_pair(7,7);

  EXPECT_TRUE(MapUtils::is_coordinate_within_player_restricted_zone(map, c));

  c = make_pair(8,8);

  EXPECT_TRUE(MapUtils::is_coordinate_within_player_restricted_zone(map, c));

  c = make_pair(9,9);

  EXPECT_FALSE(MapUtils::is_coordinate_within_player_restricted_zone(map, c));
}

TEST(SW_Engine_Maps_MapUtils, get_map_exit_direction)
{
  Dimensions dim;

  // NW corner
  Coordinate c = { 0,0 };
  EXPECT_EQ(Direction::DIRECTION_NORTH_WEST, MapUtils::get_exit_direction(Direction::DIRECTION_NORTH_WEST, dim, c));

  // NE corner
  c = { 0, 79 };
  EXPECT_EQ(Direction::DIRECTION_NORTH_EAST, MapUtils::get_exit_direction(Direction::DIRECTION_NORTH_EAST, dim, c));

  // SW corner
  c = { 19,0 };
  EXPECT_EQ(Direction::DIRECTION_SOUTH_WEST, MapUtils::get_exit_direction(Direction::DIRECTION_SOUTH_WEST, dim, c));

  // SE corner
  c = { 19,79 };
  EXPECT_EQ(Direction::DIRECTION_SOUTH_EAST, MapUtils::get_exit_direction(Direction::DIRECTION_SOUTH_EAST, dim, c));

  // Other cases
  c = { 0,5 };
  EXPECT_EQ(Direction::DIRECTION_NORTH, MapUtils::get_exit_direction(Direction::DIRECTION_NORTH, dim, c));
  EXPECT_EQ(Direction::DIRECTION_NORTH, MapUtils::get_exit_direction(Direction::DIRECTION_NORTH_WEST, dim, c));
  EXPECT_EQ(Direction::DIRECTION_NORTH, MapUtils::get_exit_direction(Direction::DIRECTION_NORTH_EAST, dim, c));
  
  c = { 5, 0 };
  EXPECT_EQ(Direction::DIRECTION_WEST, MapUtils::get_exit_direction(Direction::DIRECTION_WEST, dim, c));
  EXPECT_EQ(Direction::DIRECTION_WEST, MapUtils::get_exit_direction(Direction::DIRECTION_NORTH_WEST, dim, c));
  EXPECT_EQ(Direction::DIRECTION_WEST, MapUtils::get_exit_direction(Direction::DIRECTION_SOUTH_WEST, dim, c));

  c = { 5, 79 };

  EXPECT_EQ(Direction::DIRECTION_EAST, MapUtils::get_exit_direction(Direction::DIRECTION_EAST, dim, c));
  EXPECT_EQ(Direction::DIRECTION_EAST, MapUtils::get_exit_direction(Direction::DIRECTION_NORTH_EAST, dim, c));
  EXPECT_EQ(Direction::DIRECTION_EAST, MapUtils::get_exit_direction(Direction::DIRECTION_SOUTH_EAST, dim, c));
  
  c = { 19, 5 };

  EXPECT_EQ(Direction::DIRECTION_SOUTH, MapUtils::get_exit_direction(Direction::DIRECTION_SOUTH, dim, c));
  EXPECT_EQ(Direction::DIRECTION_SOUTH, MapUtils::get_exit_direction(Direction::DIRECTION_SOUTH_WEST, dim, c));
  EXPECT_EQ(Direction::DIRECTION_SOUTH, MapUtils::get_exit_direction(Direction::DIRECTION_SOUTH_EAST, dim, c));
}

TEST(SW_Engine_Maps_MapUtils, get_weather)
{
  Weather map_weather("36");
  Weather tile_weather("32");
  WeatherPtr no_weather;

  TilePtr tile = make_shared<FieldTile>();
  tile->set_weather(tile_weather);

  Dimensions d;
  MapPtr world_map = std::make_shared<Map>(d);
  world_map->set_map_type(MapType::MAP_TYPE_WORLD);

  MapPtr overworld_map = std::make_shared<Map>(d);
  overworld_map->set_map_type(MapType::MAP_TYPE_OVERWORLD);
  overworld_map->set_weather(map_weather);

  MapPtr underworld_map = std::make_shared<Map>(d);
  underworld_map->set_map_type(MapType::MAP_TYPE_UNDERWORLD);

  MapPtr underwater_map = std::make_shared<Map>(d);
  underwater_map->set_map_type(MapType::MAP_TYPE_UNDERWATER);

  MapPtr cosmos_map = std::make_shared<Map>(d);
  cosmos_map->set_map_type(MapType::MAP_TYPE_COSMOS);

  MapPtr air_map = std::make_shared<Map>(d);
  air_map->set_map_type(MapType::MAP_TYPE_AIR);
  air_map->set_weather(map_weather);

  EXPECT_EQ(tile_weather, *MapUtils::get_weather(world_map, tile));
  EXPECT_EQ(map_weather, *MapUtils::get_weather(overworld_map, tile));
  EXPECT_EQ(no_weather, MapUtils::get_weather(underworld_map, tile));
  EXPECT_EQ(no_weather, MapUtils::get_weather(underwater_map, tile));
  EXPECT_EQ(no_weather, MapUtils::get_weather(cosmos_map, tile));
  EXPECT_EQ(map_weather, *MapUtils::get_weather(air_map, tile));
}

TEST(SW_Engine_Maps_MapUtils, get_available_adjacent_tiles_to_creature)
{
  CreaturePtr pov_creature = std::make_shared<Creature>();
  pov_creature->set_id("pov");

  CreaturePtr adj_creature = std::make_shared<Creature>();
  adj_creature->set_id("adj");

  CreaturePtr place_creature = std::make_shared<Creature>();

  Dimensions d;
  MapPtr map = std::make_shared<Map>(d);
  GeneratorUtils::fill(map, { 0,0 }, { 5,5 }, TileType::TILE_TYPE_FIELD);
  
  MapUtils::add_or_update_location(map, pov_creature, { 1,1 });
  MapUtils::add_or_update_location(map, adj_creature, { 0,1 });

  auto avail_adj = MapUtils::get_available_adjacent_tiles_to_creature(map, pov_creature, place_creature);

  EXPECT_EQ(7, avail_adj.size());
  EXPECT_TRUE(avail_adj.find(Direction::DIRECTION_NORTH) == avail_adj.end());

  map->at(0, 1)->remove_creature();
  avail_adj = MapUtils::get_available_adjacent_tiles_to_creature(map, pov_creature, place_creature);

  vector<Direction> dirs = { Direction::DIRECTION_NORTH_EAST, Direction::DIRECTION_NORTH, Direction::DIRECTION_NORTH_WEST, Direction::DIRECTION_EAST, Direction::DIRECTION_WEST, Direction::DIRECTION_SOUTH_EAST, Direction::DIRECTION_SOUTH, Direction::DIRECTION_SOUTH_WEST };

  EXPECT_EQ(8, avail_adj.size());

  for (const Direction dir : dirs)
  {
    EXPECT_TRUE(avail_adj.find(dir) != avail_adj.end());
  }
}

TEST(SW_Engine_Maps_MapUtils, get_coastline_dirs)
{
  Dimensions d;
  MapPtr map = std::make_shared<Map>(d);
  GeneratorUtils::fill(map, { 0,0 }, { d.get_y() - 1, d.get_x() - 1 }, TileType::TILE_TYPE_SEA);

  // Case 1: sea in all directions.
  // 
  // Place a single field in the center.  It should be surrounded by sea.
  TileGenerator tg;
  TilePtr tile = tg.generate(TileType::TILE_TYPE_FIELD);
  map->insert({ 10, 10 }, tile);
  vector<Direction> dirs = MapUtils::get_coastline_directions(map, { 10, 10 });

  EXPECT_EQ(4, dirs.size());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_NORTH) != dirs.end());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_SOUTH) != dirs.end());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_EAST) != dirs.end());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_WEST) != dirs.end());

  // Case 2: sea in most directions
  tile = tg.generate(TileType::TILE_TYPE_FIELD);
  map->insert({ 10, 11 }, tile);
  dirs = MapUtils::get_coastline_directions(map, { 10, 11 });

  EXPECT_EQ(3, dirs.size());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_NORTH) != dirs.end());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_SOUTH) != dirs.end());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_EAST) != dirs.end());

  // Case 3: sea in one direction
  for (int y = 15; y < 18; y++)
  {
    for (int x = 15; x < 18; x++)
    {
      tile = tg.generate(TileType::TILE_TYPE_FIELD);
      map->insert(y, x, tile);
    }
  }

  dirs = MapUtils::get_coastline_directions(map, { 16, 17 });
  EXPECT_EQ(1, dirs.size());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_EAST) != dirs.end());

  // Case 4: landlocked
  dirs = MapUtils::get_coastline_directions(map, { 16, 16 });
  EXPECT_EQ(0, dirs.size());
}

TEST(SW_Engine_Maps_MapUtils, set_coastline_generator_dirs)
{
  FieldGenerator generator("test");

  vector<Direction> dirs = { Direction::DIRECTION_EAST };
  MapUtils::set_coastline_generator_dirs(&generator, dirs);

  EXPECT_EQ(std::to_string(true), generator.get_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_EAST));
  EXPECT_FALSE(generator.has_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST));
  EXPECT_FALSE(generator.has_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH));
  EXPECT_FALSE(generator.has_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH));

  dirs = { Direction::DIRECTION_EAST, Direction::DIRECTION_WEST, Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH };
  MapUtils::set_coastline_generator_dirs(&generator, dirs);

  EXPECT_EQ(std::to_string(true), generator.get_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH));
  EXPECT_EQ(std::to_string(true), generator.get_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH));
  EXPECT_EQ(std::to_string(true), generator.get_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_EAST));
  EXPECT_EQ(std::to_string(true), generator.get_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST));
}

TEST(SW_Engine_Maps_MapUtils, get_coordinate_location_sid)
{
  Dimensions d(100, 100);
  vector<pair<Coordinate, string>> details = { {{0,0}, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_WEST},
                                               {{28, 28}, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_WEST},
                                               {{0, 50}, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH},
                                               {{28, 41}, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH},
                                               {{0, 99}, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_EAST},
                                               {{24, 83}, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_EAST},
                                               {{50, 0}, DirectionLocationTextKeys::DIRECTION_LOCATION_WEST},
                                               {{60, 14}, DirectionLocationTextKeys::DIRECTION_LOCATION_WEST},
                                               {{50, 50}, DirectionLocationTextKeys::DIRECTION_LOCATION_MIDDLE},
                                               {{60, 43}, DirectionLocationTextKeys::DIRECTION_LOCATION_MIDDLE},
                                               {{50, 99}, DirectionLocationTextKeys::DIRECTION_LOCATION_EAST},
                                               {{66, 86}, DirectionLocationTextKeys::DIRECTION_LOCATION_EAST},
                                               {{99, 0}, DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_WEST},
                                               {{73, 17}, DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_WEST},
                                               {{99,99}, DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_EAST},
                                               {{88,91}, DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_EAST}};

  for (const auto& d_pair : details)
  {
    EXPECT_EQ(d_pair.second, MapUtils::get_coordinate_location_sid(d_pair.first, d));
  }
}

TEST(SW_Engine_MapUtils, add_preset_village)
{
  Dimensions dim;
  MapPtr map = std::make_shared<Map>(dim);

  MapUtils::add_preset_village(map, 3, 4);
  MapUtils::add_preset_village(map, 12, 5);

  EXPECT_EQ("3-4,12-5", map->get_property(MapProperties::MAP_PROPERTIES_PRESET_VILLAGE_COORDINATES));
}

TEST(SW_Engine_MapUtils, can_change_zlevel)
{
  CreaturePtr c = std::make_shared<Creature>();
  CreaturePtr fly = std::make_shared<Creature>();
  Status status(StatusIdentifiers::STATUS_ID_FLYING, true, 50, "some_spell");
  fly->set_status(StatusIdentifiers::STATUS_ID_FLYING, status);

  Dimensions dim;
  MapPtr ground = std::make_shared<Map>(dim);
  MapPtr air = std::make_shared<Map>(dim);

  ground->set_is_water_shallow(true);
  air->set_is_open_sky(true);
  air->set_map_type(MapType::MAP_TYPE_AIR);

  GeneratorUtils::fill(ground, { 0,0 }, { 19, 79 }, TileType::TILE_TYPE_FIELD);
  TileGenerator tg;
  TilePtr tile = tg.generate(TileType::TILE_TYPE_SEA);
  ground->insert({ 0,0 }, tile);

  GeneratorUtils::fill(air, { 0,0 }, { 19, 79 }, TileType::TILE_TYPE_AIR);

  UnderwaterGenerator ug(ground, "some_id");
  MapPtr uw = ug.generate(dim);
  uw->set_map_type(ug.get_map_type());

  SeaGenerator sea_gen("fdsa");
  MapPtr sea = sea_gen.generate(dim);

  // Down/up on ground map
  tile = ground->at(0, 0);
  EXPECT_FALSE(MapUtils::can_change_zlevel(c, ground, tile, Direction::DIRECTION_DOWN).first);
  c->get_skills().set_value(SkillType::SKILL_GENERAL_SWIMMING, 10);
  EXPECT_TRUE(MapUtils::can_change_zlevel(c, ground, tile, Direction::DIRECTION_DOWN).first);

  EXPECT_FALSE(MapUtils::can_change_zlevel(c, ground, tile, Direction::DIRECTION_UP).first);
  EXPECT_TRUE(MapUtils::can_change_zlevel(fly, ground, tile, Direction::DIRECTION_UP).first);

  // Down/up on underwater
  tile = uw->at(0, 0);
  EXPECT_FALSE(MapUtils::can_change_zlevel(c, uw, tile, Direction::DIRECTION_DOWN).first);
  EXPECT_FALSE(MapUtils::can_change_zlevel(fly, uw, tile, Direction::DIRECTION_DOWN).first);
  EXPECT_TRUE(MapUtils::can_change_zlevel(c, uw, tile, Direction::DIRECTION_UP).first);
  EXPECT_TRUE(MapUtils::can_change_zlevel(fly, uw, tile, Direction::DIRECTION_UP).first);

  // Can't go down in open sea
  tile = sea->at(3, 3);
  EXPECT_FALSE(MapUtils::can_change_zlevel(c, uw, tile, Direction::DIRECTION_DOWN).first);
  EXPECT_FALSE(MapUtils::can_change_zlevel(fly, uw, tile, Direction::DIRECTION_DOWN).first);

  // Down/up for open air
  tile = air->at(0, 0);
  EXPECT_TRUE(MapUtils::can_change_zlevel(c, air, tile, Direction::DIRECTION_DOWN).first);
  EXPECT_TRUE(MapUtils::can_change_zlevel(fly, air, tile, Direction::DIRECTION_DOWN).first);
  EXPECT_FALSE(MapUtils::can_change_zlevel(c, air, tile, Direction::DIRECTION_UP).first);
  EXPECT_FALSE(MapUtils::can_change_zlevel(fly, air, tile, Direction::DIRECTION_UP).first);
}

TEST(SW_Engine_MapUtils, should_creature_move_to_new_map)
{
  CreaturePtr c = std::make_shared<Creature>();

  CreaturePtr water = std::make_shared<Creature>();
  water->set_breathes(BreatheType::BREATHE_TYPE_ALL);

  CreaturePtr air = std::make_shared<Creature>();
  Status status(StatusIdentifiers::STATUS_ID_FLYING, true, 50, "some_spell");
  air->set_status(StatusIdentifiers::STATUS_ID_FLYING, status);

  map<MapType, std::map<CreaturePtr, bool>> outcomes = { {MapType::MAP_TYPE_AIR, {{nullptr, false}, {c, false}, {water, false}, {air, true}}},
                                                         {MapType::MAP_TYPE_COSMOS, {{nullptr, false}, {c, true}, {water, true}, {air, true}}},
                                                         {MapType::MAP_TYPE_OVERWORLD, {{nullptr, false}, {c, true}, {water, true}, {air, true}}},
                                                         {MapType::MAP_TYPE_UNDERWORLD, {{nullptr, false}, {c, true}, {water, true}, {air, true}}},
                                                         {MapType::MAP_TYPE_UNDERWATER, {{nullptr, false}, {c, false}, {water, true}, {air, false}}} };

  for (const auto& o_pair : outcomes)
  {
    std::map<CreaturePtr, bool> creature_checks = o_pair.second;

    for (const auto& c_pair : creature_checks)
    {
      EXPECT_EQ(c_pair.second, MapUtils::should_creature_move_to_new_map_type(c_pair.first, o_pair.first));
    }
  }
}

TEST(SW_Engine_MapUtils, get_lore_skill_for_terrain)
{
  std::map<TileType, SkillType> skills = { {TileType::TILE_TYPE_DESERT, SkillType::SKILL_GENERAL_DESERT_LORE}, 
                                           {TileType::TILE_TYPE_FOREST, SkillType::SKILL_GENERAL_FOREST_LORE}, 
                                           {TileType::TILE_TYPE_MARSH, SkillType::SKILL_GENERAL_MARSH_LORE}, 
                                           {TileType::TILE_TYPE_MOUNTAINS, SkillType::SKILL_GENERAL_MOUNTAIN_LORE},
                                           {TileType::TILE_TYPE_SEA, SkillType::SKILL_GENERAL_OCEAN_LORE},
                                           {TileType::TILE_TYPE_BARROW, SkillType::SKILL_UNDEFINED} };

  TileGenerator tg;

  for (const auto& s_pair : skills)
  {
    TilePtr tile = tg.generate(s_pair.first);
    EXPECT_EQ(s_pair.second, MapUtils::get_lore_skill_for_terrain(tile));
  }
}