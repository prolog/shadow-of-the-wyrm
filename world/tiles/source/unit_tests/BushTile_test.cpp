#include "gtest/gtest.h"

TEST(SL_World_Tiles_BushTile, type_is_TILE_TYPE_BUSH)
{
  BushTile bush_tile;

  EXPECT_EQ(TileType::TILE_TYPE_BUSH, bush_tile.get_tile_type());
}
