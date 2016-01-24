#include "gtest/gtest.h"

TEST(SW_World_Tiles_ForestTile, type_is_TILE_TYPE_FOREST)
{
  ForestTile forest_tile;

  EXPECT_EQ(TileType::TILE_TYPE_FOREST, forest_tile.get_tile_type());
}

TEST(SW_World_Tiles_ForestTile, serialization_id)
{
  ForestTile forest_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FOREST_TILE, forest_tile.get_class_identifier());
}

