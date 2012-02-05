#include "gtest/gtest.h"

TEST(SL_World_Tiles_CavernTile, type_is_TILE_TYPE_CAVERN)
{
  CavernTile cavern_tile;

  EXPECT_EQ(TILE_TYPE_CAVERN, cavern_tile.get_tile_type());
}
