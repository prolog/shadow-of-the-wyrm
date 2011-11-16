#include "gtest/gtest.h"

TEST(SL_World_Tiles_WheatTile, type_is_TILE_TYPE_WHEAT)
{
  WheatTile wheat_tile;

  EXPECT_EQ(TILE_TYPE_WHEAT, wheat_tile.get_tile_type());
}
