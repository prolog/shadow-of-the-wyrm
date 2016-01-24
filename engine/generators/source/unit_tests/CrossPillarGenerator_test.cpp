#include "gtest/gtest.h"
#include "FieldGenerator.hpp"

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

