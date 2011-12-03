#include "gtest/gtest.h"

TEST(SL_World_Tiles_DownStaircaseTile, type_is_TILE_TYPE_STAIRCASE)
{
  DownStaircaseTile dst;

  EXPECT_EQ(TILE_TYPE_DOWN_STAIRCASE, dst.get_tile_type());
}

TEST(SL_World_Tiles_DownStaircaseTile, staircase_type)
{
  DownStaircaseTile dst;

  EXPECT_EQ(STAIRCASE_DOWN, dst.get_staircase_type());
}
