#include "gtest/gtest.h"

TEST(SW_Engine_Maps_TileUtils, get_opposite_tile_type)
{
  EXPECT_EQ(TileType::TILE_TYPE_UP_STAIRCASE, TileUtils::get_opposite_tile_type(TileType::TILE_TYPE_DOWN_STAIRCASE));

  EXPECT_EQ(TileType::TILE_TYPE_DOWN_STAIRCASE, TileUtils::get_opposite_tile_type(TileType::TILE_TYPE_UP_STAIRCASE));

  EXPECT_EQ(TileType::TILE_TYPE_CASTLE, TileUtils::get_opposite_tile_type(TileType::TILE_TYPE_CASTLE));

  EXPECT_EQ(TileType::TILE_TYPE_FIELD, TileUtils::get_opposite_tile_type(TileType::TILE_TYPE_FIELD));
}

