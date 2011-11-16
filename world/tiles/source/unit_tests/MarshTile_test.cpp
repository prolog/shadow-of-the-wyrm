#include "gtest/gtest.h"

TEST(SL_World_Tiles_MarshTile, type_is_TILE_TYPE_MARSH)
{
  MarshTile marsh_tile;

  EXPECT_EQ(TILE_TYPE_MARSH, marsh_tile.get_tile_type());
}
