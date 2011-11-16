#include "gtest/gtest.h"

TEST(SL_World_Tiles_ReedsTile, type_is_TILE_TYPE_REEDS)
{
  ReedsTile reeds_tile;

  EXPECT_EQ(TILE_TYPE_REEDS, reeds_tile.get_tile_type());
}
