#include "gtest/gtest.h"

TEST(SW_World_Tiles_IceFieldTile, non_blocking_with_null_creature)
{
  IceFieldTile if_tile;
  EXPECT_FALSE(if_tile.get_is_blocking(nullptr));
}

TEST(SW_World_Tiles_IceFieldTile, type_is_TILE_TYPE_ICE_FIELD)
{
  IceFieldTile if_tile;

  EXPECT_EQ(TileType::TILE_TYPE_ICE_FIELD, if_tile.get_tile_type());
}

TEST(SW_World_Tiles_IceFieldTile, serialization_id)
{
  IceFieldTile if_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ICE_FIELD_TILE, if_tile.get_class_identifier());
}

