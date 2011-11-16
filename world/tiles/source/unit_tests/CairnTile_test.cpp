#include "gtest/gtest.h"

TEST(SL_World_Tiles_CairnTile, type_is_TILE_TYPE_CAIRN)
{
  CairnTile cairn_tile;

  EXPECT_EQ(TILE_TYPE_CAIRN, cairn_tile.get_tile_type());
}
