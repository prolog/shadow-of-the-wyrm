#include "gtest/gtest.h"

TEST(SL_World_Tiles_ForestTile, type_is_TILE_TYPE_FOREST)
{
  ForestTile forest_tile;

  EXPECT_EQ(TILE_TYPE_FOREST, forest_tile.get_tile_type());
}
