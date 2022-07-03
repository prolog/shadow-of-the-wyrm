#include "gtest/gtest.h"
#include "FieldTile.hpp"
#include "MapProperties.hpp"

class SW_Engine_Map : public ::testing::Test
{
  public:
    string make_key(const Coordinate& c);
    Coordinate convert_map_key_to_coordinate(const string &s);
    ClassIdentifier get_class_identifier();
    
    MapPtr make_map() const;
};

string SW_Engine_Map::make_key(const Coordinate& c)
{
  MapPtr map = make_map();

  return MapUtils::convert_coordinate_to_map_key(c);
}

Coordinate SW_Engine_Map::convert_map_key_to_coordinate(const string& key)
{
  return MapUtils::convert_map_key_to_coordinate(key);
}

ClassIdentifier SW_Engine_Map::get_class_identifier()
{
  MapPtr map = make_map();

  return map->get_class_identifier();
}

MapPtr SW_Engine_Map::make_map() const
{
  Dimensions d;
  MapPtr map = std::make_shared<Map>(d);

  return map;
}

TEST_F(SW_Engine_Map, tile_transforms)
{
  TileTransform tt1(Coordinate(4,5), TileType::TILE_TYPE_FIELD, TileType::TILE_TYPE_UNDEFINED, {});
  TileTransform tt2(Coordinate(5,6), TileType::TILE_TYPE_MARSH, TileType::TILE_TYPE_UNDEFINED, {});
  TileTransformContainer ttc;

  ttc.insert(make_pair(12345, vector<TileTransform>{tt1}));
  ttc.insert(make_pair(65789, vector<TileTransform>{tt2}));

  Dimensions tt_dim;
  MapPtr map = std::make_shared<Map>(tt_dim);
  
  map->set_tile_transforms(ttc);

  Dimensions tt_dim2;
  MapPtr map2 = std::make_shared<Map>(tt_dim2);

  EXPECT_FALSE(*map == *map2);
}

TEST_F(SW_Engine_Map, coordinate_to_key)
{
  Coordinate c(10, 1);

  string key = make_key(c);

  EXPECT_EQ("10-1", key);

  c.first = 18;
  c.second = 67;

  key = make_key(c);

  EXPECT_EQ("18-67", key);
}

TEST_F(SW_Engine_Map, key_to_coordinate)
{
  string key = "18-67";

  Coordinate c = convert_map_key_to_coordinate(key);

  EXPECT_EQ(c.first, 18);
  EXPECT_EQ(c.second, 67);
}

TEST_F(SW_Engine_Map, map_type_allows_updates)
{
  MapPtr map = make_map();
  map->set_map_type(MapType::MAP_TYPE_UNDERWORLD);

  // By default, all maps should allow updates.
  EXPECT_TRUE(map->get_allow_creature_updates());

  // World maps don't, however!
  map->set_map_type(MapType::MAP_TYPE_WORLD);

  EXPECT_FALSE(map->get_allow_creature_updates());

  // Switch back to overworld.  Should be fine again.
  map->set_map_type(MapType::MAP_TYPE_OVERWORLD);

  EXPECT_TRUE(map->get_allow_creature_updates());

  map->set_allow_creature_updates(false);

  EXPECT_FALSE(map->get_allow_creature_updates());
}

TEST_F(SW_Engine_Map, serialization_id)
{
  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAP, get_class_identifier());
}

TEST_F(SW_Engine_Map, saveload)
{
  MapPtr map = make_map();
  map->set_property("foo", "bar");
  vector<Coordinate> coords = {{0,1},{2,2},{3,3},{18,56}};
  map->set_preset_locations(coords);
  map->set_allow_creature_creation(false);
  map->set_allow_creature_updates(false);

  ScriptDetails sd;
  sd.set_chance(22);
  sd.set_script("some/script.lua");
  map->add_event_script("aaa", sd);

  MapPtr map2 = make_map();

  ostringstream ss;
  map->serialize(ss);

  istringstream iss(ss.str());
  map2->deserialize(iss);

  EXPECT_TRUE(*map == *map2);
  EXPECT_EQ("bar", map2->get_property("foo"));
  EXPECT_EQ(coords, map2->get_preset_locations());
  EXPECT_FALSE(map2->get_allow_creature_creation());
  EXPECT_FALSE(map2->get_allow_creature_updates());
}

TEST_F(SW_Engine_Map, underwater_maps_submerge_tiles)
{
  TilePtr tile = std::make_shared<FieldTile>();
  MapPtr map = make_map();
  map->set_map_type(MapType::MAP_TYPE_UNDERWATER);

  EXPECT_FALSE(tile->get_submerged());

  map->insert({4,4}, tile);

  EXPECT_TRUE(map->at({4,4})->get_submerged());
}

TEST_F(SW_Engine_Map, default_race_id_copied_correctly)
{
  MapPtr map = make_map();
  map->set_default_race_id("test");

  MapPtr map2 = std::make_shared<Map>(*map);

  EXPECT_EQ("test", map2->get_default_race_id());
}

TEST_F(SW_Engine_Map, get_generation_coordinates)
{
  MapPtr map = make_map();
  pair<Coordinate, Coordinate> expected = make_pair(make_pair(0,0), make_pair(19, 79));

  EXPECT_EQ(expected, map->get_generation_coordinates());

  map->set_property(MapProperties::MAP_PROPERTIES_GENERATION_COORDINATES, "5,5,17,50");

  expected = make_pair(make_pair(5,5), make_pair(17,50));

  EXPECT_EQ(expected, map->get_generation_coordinates());
}

TEST_F(SW_Engine_Map, get_starting_location)
{
  MapPtr map = make_map();
  Coordinate exp = { 0, 0 };
  EXPECT_EQ(exp, map->get_starting_location());

  std::map<string, string> props = { {MapProperties::MAP_PROPERTIES_COASTLINE_NORTH, std::to_string(true)},
                                     {MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH, std::to_string(true)},
                                     {MapProperties::MAP_PROPERTIES_COASTLINE_EAST, std::to_string(true)},
                                     {MapProperties::MAP_PROPERTIES_COASTLINE_WEST, std::to_string(true)}};

  for (const auto& p_pair : props)
  {
    map->set_property(p_pair.first, p_pair.second);
  }

  EXPECT_EQ(exp, map->get_starting_location());

  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH, std::to_string(false));
  exp = { 0, 39 };

  EXPECT_EQ(exp, map->get_starting_location());

  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH, std::to_string(true));
  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH, std::to_string(false));
  exp = { 19, 39 };

  EXPECT_EQ(exp, map->get_starting_location());

  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH, std::to_string(true));
  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST, std::to_string(false));
  exp = { 9, 0 };

  EXPECT_EQ(exp, map->get_starting_location());

  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST, std::to_string(true));
  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_EAST, std::to_string(false));
  exp = { 9, 79 };

  EXPECT_EQ(exp, map->get_starting_location());
}

TEST_F(SW_Engine_Map, set_secondary_terrain)
{
  vector<TileType> tts = { TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_DESERT };
  MapPtr map = make_map();
  map->set_secondary_terrain(tts);
  vector<TileType> tts_new = map->get_secondary_terrain();

  EXPECT_EQ(2, tts_new.size());

  for (const auto tt : tts)
  {
    EXPECT_TRUE(std::find(tts_new.begin(), tts_new.end(), tt) != tts_new.end());
  }
}

TEST_F(SW_Engine_Map, add_secondary_terrain)
{
  vector<TileType> tts = { TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_DESERT };
  MapPtr map = make_map();

  for (int i = 0; i < 3; i++)
  {
    for (const auto tt : tts)
    {
      map->add_secondary_terrain(tt);
    }
  }

  vector<TileType> tts_new = map->get_secondary_terrain();

  EXPECT_EQ(2, tts_new.size());

  for (const auto tt : tts)
  {
    EXPECT_TRUE(std::find(tts_new.begin(), tts_new.end(), tt) != tts_new.end());
  }

}

TEST_F(SW_Engine_Map, get_secondary_terrain)
{
  MapPtr map = make_map();

  EXPECT_TRUE(map->get_secondary_terrain().empty());

  vector<TileType> ttv = { TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_RIVER };

  ostringstream ss;
  ss << static_cast<int>(TileType::TILE_TYPE_SEA) << "," << static_cast<int>(TileType::TILE_TYPE_RIVER);
  map->set_property(MapProperties::MAP_PROPERTIES_SECONDARY_TERRAIN, ss.str());

  vector<TileType> sec_ter = map->get_secondary_terrain();

  EXPECT_FALSE(sec_ter.empty());
  EXPECT_EQ(2, sec_ter.size());
  
  for (const auto tt : ttv)
  {
    EXPECT_TRUE(std::find(sec_ter.begin(), sec_ter.end(), tt) != sec_ter.end());
  }
}

TEST_F(SW_Engine_Map, get_coastline_directions)
{
  MapPtr map = make_map();

  EXPECT_TRUE(map->get_coastline_directions().empty());

  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH, std::to_string(true));

  vector<Direction> dirs = map->get_coastline_directions();

  EXPECT_EQ(1, dirs.size());
  EXPECT_EQ(Direction::DIRECTION_NORTH, dirs[0]);

  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH, std::to_string(true));
  map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST, std::to_string(true));
  dirs = map->get_coastline_directions();

  EXPECT_EQ(3, dirs.size());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_NORTH) != dirs.end());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_SOUTH) != dirs.end());
  EXPECT_TRUE(std::find(dirs.begin(), dirs.end(), Direction::DIRECTION_WEST) != dirs.end());
}

TEST_F(SW_Engine_Map, get_is_water_shallow)
{
  MapPtr map = make_map();
  
  EXPECT_TRUE(map->get_is_water_shallow());

  map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, to_string(true));

  EXPECT_TRUE(map->get_is_water_shallow());

  map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, to_string(false));

  EXPECT_FALSE(map->get_is_water_shallow());
}
