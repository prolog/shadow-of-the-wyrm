#include "gtest/gtest.h"

TEST(SL_World_Tiles_TreeTile, type_is_TILE_TYPE_TREE)
{
  TreeTile tree_tile;

  EXPECT_EQ(TILE_TYPE_TREE, tree_tile.get_tile_type());
}
