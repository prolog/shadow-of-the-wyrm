#include "gtest/gtest.h"

TEST(SL_World_Tiles_EvergreenTreeTile, type_is_TILE_TYPE_EVERGREEN_TREE)
{
  EvergreenTreeTile evergreen_tree_tile;

  EXPECT_EQ(TILE_TYPE_EVERGREEN_TREE, evergreen_tree_tile.get_tile_type());
}

TEST(SL_World_Tiles_EvergreenTreeTile, serialization_id)
{
  EvergreenTreeTile evergreen_tree_tile;

  EXPECT_EQ(CLASS_ID_EVERGREEN_TREE_TILE, evergreen_tree_tile.get_class_identifier());
}
