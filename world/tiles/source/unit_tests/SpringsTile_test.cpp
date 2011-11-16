#include "gtest/gtest.h"

TEST(SL_World_Tiles_SpringsTile, type_is_TILE_TYPE_SPRINGS)
{
  SpringsTile springs_tile;

  EXPECT_EQ(TILE_TYPE_SPRINGS, springs_tile.get_tile_type());
}
