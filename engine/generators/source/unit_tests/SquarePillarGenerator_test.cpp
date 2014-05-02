#include "gtest/gtest.h"
#include "FieldGenerator.hpp"

TEST(SL_World_Generators_SquarePillarGenerator, expected_shape)
{
  FieldGenerator fg("foo");
  Dimensions dim;

  MapPtr map = fg.generate(dim);

  SquarePillarGenerator spg;
  spg.generate(map, 0, 0);

  for (int i = 0; i <= spg.get_height(); i++)
  {
    for (int j = 0; j <= spg.get_width(); j++)
    {
      TilePtr tile = map->at(i, j);
      EXPECT_TRUE(tile->get_tile_type() == TILE_TYPE_ROCK);
    }
  }
}

