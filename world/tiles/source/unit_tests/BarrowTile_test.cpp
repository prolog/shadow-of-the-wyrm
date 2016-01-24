#include "gtest/gtest.h"

TEST(SW_World_Tiles_BarrowTile, type_is_TILE_TYPE_BARROW)
{
  BarrowTile barrow_tile;

  EXPECT_EQ(TileType::TILE_TYPE_BARROW, barrow_tile.get_tile_type());
}

TEST(SW_World_Tiles_BarrowTile, serialization_id)
{
  BarrowTile barrow_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BARROW_TILE, barrow_tile.get_class_identifier());
}

