#include "gtest/gtest.h"

TEST(SL_World_Tiles_ScrubTile, type_is_TILE_TYPE_SCRUB)
{
  ScrubTile scrub_tile;

  EXPECT_EQ(TILE_TYPE_SCRUB, scrub_tile.get_tile_type());
}
