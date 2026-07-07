#include "gtest/gtest.h"

TEST(SW_World_Tiles_IcebergTile, non_blocking_with_null_creature)
{
  IcebergTile ib_tile;
  EXPECT_FALSE(ib_tile.get_is_blocking(nullptr));
}

TEST(SW_World_Tiles_IcebergTile, type_is_TILE_TYPE_ICEBERG)
{
  IcebergTile ib_tile;

  EXPECT_EQ(TileType::TILE_TYPE_ICEBERG, ib_tile.get_tile_type());
}

TEST(SW_World_Tiles_IcebergTile, serialization_id)
{
  IcebergTile ib_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ICEBERG, ib_tile.get_class_identifier());
}

