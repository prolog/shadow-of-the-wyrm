#include "gtest/gtest.h"

TEST(SL_World_Tiles_WeedsTile, type_is_TILE_TYPE_WEEDS)
{
  WeedsTile weeds_tile;

  EXPECT_EQ(TILE_TYPE_WEEDS, weeds_tile.get_tile_type());
}
