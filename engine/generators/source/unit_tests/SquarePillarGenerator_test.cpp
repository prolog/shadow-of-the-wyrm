#include "gtest/gtest.h"
#include "FieldGenerator.hpp"

TEST(SL_World_Generators_SquarePillarGenerator, expected_shape)
{
  FieldGenerator fg("foo");
  Dimensions dim;

  MapPtr map = fg.generate(dim);

  SquarePillarGenerator spg;
  spg.generate(map, 0, 0);

  for (int i = 0; i <= spg.get_height() - 1; i++)
  {
    for (int j = 0; j <= spg.get_width() - 1; j++)
    {
      TilePtr tile = map->at(i, j);
      EXPECT_TRUE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);
    }
  }

  // Check the edges to make sure the number of tiles is correct.
  TilePtr tile = map->at(0, 2);
  EXPECT_FALSE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);

  tile = map->at(2, 0);
  EXPECT_FALSE(tile->get_tile_type() == TileType::TILE_TYPE_ROCK);
}

