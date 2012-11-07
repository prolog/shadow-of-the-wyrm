#include "gtest/gtest.h"

TEST(SL_World_Tiles_GraveTile, type_is_TILE_TYPE_GRAVE)
{
  GraveTile grave_tile;

  EXPECT_EQ(TILE_TYPE_GRAVE, grave_tile.get_tile_type());
}

TEST(SL_World_Tiles_GraveTile, serialization_id)
{
  GraveTile grave_tile;

  EXPECT_EQ(CLASS_ID_GRAVE_TILE, grave_tile.get_class_identifier());
}

