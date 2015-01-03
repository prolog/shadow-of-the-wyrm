#include "gtest/gtest.h"

TEST(SL_World_Tiles_CastleTile, type_is_TILE_TYPE_CASTLE)
{
  CastleTile castle_tile;

  EXPECT_EQ(TILE_TYPE_CASTLE, castle_tile.get_tile_type());
}

TEST(SL_World_Tiles_CastleTile, tile_description_sid)
{
  CastleTile castle_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_CASTLE, castle_tile.get_tile_description_sid());
}

TEST(SL_World_Tiles_CastleTile, serialization_id)
{
  CastleTile castle_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CASTLE_TILE, castle_tile.get_class_identifier());
}

