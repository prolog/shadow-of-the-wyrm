#include "gtest/gtest.h"

TEST(SW_World_Tiles_VoidTile, type_is_TILE_TYPE_VOID)
{
  VoidTile void_tile;

  EXPECT_EQ(TileType::TILE_TYPE_VOID, void_tile.get_tile_type());
}

TEST(SW_World_Tiles_VoidTile, serialization_id)
{
  VoidTile void_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_VOID_TILE, void_tile.get_class_identifier());
}

