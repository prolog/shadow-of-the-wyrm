#include "gtest/gtest.h"

TEST(SL_World_Tiles_MountainsTile, type_is_TILE_TYPE_MOUNTAINS)
{
  MountainsTile mountains_tile;

  EXPECT_EQ(TILE_TYPE_MOUNTAINS, mountains_tile.get_tile_type());
}
