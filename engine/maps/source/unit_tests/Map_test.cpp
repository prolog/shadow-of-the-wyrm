#include "gtest/gtest.h"

class SL_Engine_Map : public ::testing::Test
{
  public:
    string make_key(const Coordinate& c);
    Coordinate convert_map_key_to_coordinate(const string &s);
    ClassIdentifier get_class_identifier();
    
    MapPtr make_map() const;
};

string SL_Engine_Map::make_key(const Coordinate& c)
{
  MapPtr map = make_map();

  return MapUtils::convert_coordinate_to_map_key(c);
}

Coordinate SL_Engine_Map::convert_map_key_to_coordinate(const string& key)
{
  return MapUtils::convert_map_key_to_coordinate(key);
}

ClassIdentifier SL_Engine_Map::get_class_identifier()
{
  MapPtr map = make_map();

  return map->get_class_identifier();
}

MapPtr SL_Engine_Map::make_map() const
{
  Dimensions d;
  MapPtr map = std::make_shared<Map>(d);

  return map;
}

TEST_F(SL_Engine_Map, coordinate_to_key)
{
  Coordinate c(10, 1);

  string key = make_key(c);

  EXPECT_EQ("10-1", key);

  c.first = 18;
  c.second = 67;

  key = make_key(c);

  EXPECT_EQ("18-67", key);
}

TEST_F(SL_Engine_Map, key_to_coordinate)
{
  string key = "18-67";

  Coordinate c = convert_map_key_to_coordinate(key);

  EXPECT_EQ(c.first, 18);
  EXPECT_EQ(c.second, 67);
}

TEST_F(SL_Engine_Map, map_type_allows_updates)
{
  MapPtr map = make_map();
  map->set_map_type(MAP_TYPE_UNDERWORLD);

  // By default, all maps should allow updates.
  EXPECT_TRUE(map->get_allow_creature_updates());

  // World maps don't, however!
  map->set_map_type(MAP_TYPE_WORLD);

  EXPECT_FALSE(map->get_allow_creature_updates());

  // Switch back to overworld.  Should be fine again.
  map->set_map_type(MAP_TYPE_OVERWORLD);

  EXPECT_TRUE(map->get_allow_creature_updates());

  map->set_allow_creature_updates(false);

  EXPECT_FALSE(map->get_allow_creature_updates());
}

TEST_F(SL_Engine_Map, serialization_id)
{
  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAP, get_class_identifier());
}

