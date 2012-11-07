#include "gtest/gtest.h"

TEST(SL_World_Tiles_SeaTile, type_is_TILE_TYPE_SEA)
{
  SeaTile sea_tile;

  EXPECT_EQ(TILE_TYPE_SEA, sea_tile.get_tile_type());
}

TEST(SL_World_Tiles_SeaTile, serialization_id)
{
  SeaTile sea_tile;

  EXPECT_EQ(CLASS_ID_SEA_TILE, sea_tile.get_class_identifier());
}

