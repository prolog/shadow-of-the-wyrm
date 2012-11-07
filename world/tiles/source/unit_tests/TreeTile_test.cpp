#include "gtest/gtest.h"

TEST(SL_World_Tiles_TreeTile, type_is_TILE_TYPE_TREE)
{
  TreeTile tree_tile;

  EXPECT_EQ(TILE_TYPE_TREE, tree_tile.get_tile_type());
}

TEST(SL_World_Tiles_TreeTile, serialization_id)
{
  TreeTile tree_tile;

  EXPECT_EQ(CLASS_ID_TREE_TILE, tree_tile.get_class_identifier());
}
