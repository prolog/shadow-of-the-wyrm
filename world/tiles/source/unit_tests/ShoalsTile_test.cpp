#include "gtest/gtest.h"

TEST(SL_World_Tiles_ShoalsTile, type_is_TILE_TYPE_SHOALS)
{
  ShoalsTile shoals_tile;

  EXPECT_EQ(TILE_TYPE_SHOALS, shoals_tile.get_tile_type());
}
