#include "gtest/gtest.h"

TEST(SW_World_Tiles_MagicalTreeTile, type_is_TILE_TYPE_MAGICAL_TREE)
{
  MagicalTreeTile magical_tree_tile;

  EXPECT_EQ(TileType::TILE_TYPE_MAGICAL_TREE, magical_tree_tile.get_tile_type());
}

TEST(SW_World_Tiles_MagicalTreeTile, serialization_id)
{
  MagicalTreeTile magical_tree_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAGICAL_TREE_TILE, magical_tree_tile.get_class_identifier());
}

