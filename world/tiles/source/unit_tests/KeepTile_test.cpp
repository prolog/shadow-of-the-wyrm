#include "gtest/gtest.h"

TEST(SL_World_Tiles_KeepTile, type_is_TILE_TYPE_KEEP)
{
  KeepTile keep_tile;

  EXPECT_EQ(TILE_TYPE_KEEP, keep_tile.get_tile_type());
}

TEST(SL_World_Tiles_KeepTile, tile_description_sid)
{
  KeepTile keep_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_KEEP, keep_tile.get_tile_description_sid());
}

TEST(SL_World_Tiles_KeepTile, serialization_id)
{
  KeepTile keep_tile;

  EXPECT_EQ(CLASS_ID_KEEP_TILE, keep_tile.get_class_identifier());
}
