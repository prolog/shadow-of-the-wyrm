#include "gtest/gtest.h"

TEST(SL_World_Tiles_FruitTreeTile, type_is_TILE_TYPE_FRUIT_TREE)
{
  FruitTreeTile fruit_tree_tile;

  EXPECT_EQ(TILE_TYPE_FRUIT_TREE, fruit_tree_tile.get_tile_type());
}

TEST(SL_World_Tiles_FruitTreeTile, serialization_id)
{
  FruitTreeTile fruit_tree_tile;

  EXPECT_EQ(CLASS_ID_FRUIT_TREE_TILE, fruit_tree_tile.get_class_identifier());
}
