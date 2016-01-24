#include "gtest/gtest.h"

TEST(SW_World_Tiles_TreeTile, type_is_TILE_TYPE_TREE)
{
  TreeTile tree_tile;

  EXPECT_EQ(TileType::TILE_TYPE_TREE, tree_tile.get_tile_type());
}

TEST(SW_World_Tiles_TreeTile, serialization_id)
{
  TreeTile tree_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TREE_TILE, tree_tile.get_class_identifier());
}
