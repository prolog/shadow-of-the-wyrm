#include "gtest/gtest.h"

TEST(SW_World_Tiles_FruitTreeTile, type_is_TILE_TYPE_FRUIT_TREE)
{
  FruitTreeTile fruit_tree_tile;

  EXPECT_EQ(TileType::TILE_TYPE_FRUIT_TREE, fruit_tree_tile.get_tile_type());
}

TEST(SW_World_Tiles_FruitTreeTile, serialization_id)
{
  FruitTreeTile fruit_tree_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FRUIT_TREE_TILE, fruit_tree_tile.get_class_identifier());
}
