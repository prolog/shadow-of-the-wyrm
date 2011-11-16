#include "gtest/gtest.h"

TEST(SL_World_Tiles_SeaTile, type_is_TILE_TYPE_SEA)
{
  SeaTile sea_tile;

  EXPECT_EQ(TILE_TYPE_SEA, sea_tile.get_tile_type());
}
