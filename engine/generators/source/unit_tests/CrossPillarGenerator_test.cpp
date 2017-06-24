#include "gtest/gtest.h"
#include "FieldGenerator.hpp"

// This needs to be in one of the generator unit tests - here is as good
// as anywhere!
TEST(SW_World_Generators_CrossPillarGenerator, recursive_properties)
{
  FieldGenerator fg("hi!");
  map<string, string> properties = {{"AAA", "123"},
                                    {"BBB", "test"},
                                    {"CCC", "this should come through"},
                                    {"CCC_RECURSIVE", std::to_string(true)}};

  fg.set_additional_properties(properties);

  map<string, string> rec_properties = fg.get_recursive_properties();

  EXPECT_EQ(2, rec_properties.size());

  auto r_it = rec_properties.find("CCC");
  EXPECT_TRUE(r_it != rec_properties.end());

  r_it = rec_properties.find("CCC_RECURSIVE");
  EXPECT_TRUE(r_it != rec_properties.end());
}

TEST(SW_World_Generators_CrossPillarGenerator, expected_shape)
{
  FieldGenerator fg("foo");
  Dimensions dim;

  MapPtr map = fg.generate(dim);

  CrossPillarGenerator cpg;
  cpg.generate(map, 0, 0);

  TilePtr tile = map->at(0, 1);
  EXPECT_TRUE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);

  tile = map->at(1, 1);
  EXPECT_TRUE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);

  tile = map->at(2, 1);
  EXPECT_TRUE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);

  tile = map->at(1, 0);
  EXPECT_TRUE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);

  tile = map->at(1, 2);
  EXPECT_TRUE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);
}

