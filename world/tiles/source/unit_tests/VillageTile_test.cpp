#include "gtest/gtest.h"

TEST(SL_World_Tiles_VillageTile, type_is_TILE_TYPE_VILLAGE)
{
  VillageTile village_tile;

  EXPECT_EQ(TILE_TYPE_VILLAGE, village_tile.get_tile_type());
}
