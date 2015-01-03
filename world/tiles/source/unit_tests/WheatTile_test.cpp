#include "gtest/gtest.h"

TEST(SL_World_Tiles_WheatTile, type_is_TILE_TYPE_WHEAT)
{
  WheatTile wheat_tile;

  EXPECT_EQ(TileType::TILE_TYPE_WHEAT, wheat_tile.get_tile_type());
}

TEST(SL_World_Tiles_WheatTile, serialization_id)
{
  WheatTile wheat_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WHEAT_TILE, wheat_tile.get_class_identifier());
}

