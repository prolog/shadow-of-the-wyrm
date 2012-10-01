#include "gtest/gtest.h"
#include <boost/make_shared.hpp>

class SL_Engine_Map : public ::testing::Test
{
  public:
    string make_key(const Coordinate& c);
    Coordinate convert_map_key_to_coordinate(const string &s);
    
    MapPtr make_map() const;
};

string SL_Engine_Map::make_key(const Coordinate& c)
{
  MapPtr map = make_map();

  return map->make_map_key(c.first, c.second);
}

Coordinate SL_Engine_Map::convert_map_key_to_coordinate(const string& key)
{
  MapPtr map = make_map();

  return MapUtils::convert_map_key_to_coordinate(key);
}

MapPtr SL_Engine_Map::make_map() const
{
  Dimensions d;
  MapPtr map = boost::make_shared<Map>(d);

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

