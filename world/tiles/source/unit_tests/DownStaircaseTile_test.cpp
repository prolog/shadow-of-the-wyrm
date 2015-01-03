#include "gtest/gtest.h"

TEST(SL_World_Tiles_DownStaircaseTile, type_is_TILE_TYPE_STAIRCASE)
{
  DownStaircaseTile dst;

  EXPECT_EQ(TileType::TILE_TYPE_DOWN_STAIRCASE, dst.get_tile_type());
}

TEST(SL_World_Tiles_DownStaircaseTile, staircase_type)
{
  DownStaircaseTile dst;

  EXPECT_EQ(STAIRCASE_DOWN, dst.get_staircase_type());
}

TEST(SL_World_Tiles_DownStaircaseTile, serialization_id)
{
  DownStaircaseTile dst;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DOWN_STAIRCASE_TILE, dst.get_class_identifier());
}

