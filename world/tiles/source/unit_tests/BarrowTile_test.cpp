#include "gtest/gtest.h"

TEST(SL_World_Tiles_BarrowTile, type_is_TILE_TYPE_BARROW)
{
  BarrowTile barrow_tile;

  EXPECT_EQ(TILE_TYPE_BARROW, barrow_tile.get_tile_type());
}

TEST(SL_World_Tiles_BarrowTile, serialization_id)
{
  BarrowTile barrow_tile;

  EXPECT_EQ(CLASS_ID_BARROW_TILE, barrow_tile.get_class_identifier());
}

