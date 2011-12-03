#include "gtest/gtest.h"

TEST(SL_World_Tiles_UpStaircaseTile, type_is_TILE_TYPE_STAIRCASE)
{
  UpStaircaseTile ust;

  EXPECT_EQ(TILE_TYPE_UP_STAIRCASE, ust.get_tile_type());
}

TEST(SL_World_Tiles_UpStaircaseTile, staircase_type)
{
  UpStaircaseTile ust;

  EXPECT_EQ(STAIRCASE_UP, ust.get_staircase_type());
}
