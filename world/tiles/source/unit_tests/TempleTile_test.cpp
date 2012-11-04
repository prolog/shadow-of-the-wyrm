#include "gtest/gtest.h"

TEST(SL_World_Tiles_TempleTile, type_is_TILE_TYPE_TEMPLE)
{
  TempleTile temple_tile;

  EXPECT_EQ(TILE_TYPE_TEMPLE, temple_tile.get_tile_type());
}

TEST(SL_World_Tiles_TempleTile, tile_description_sid)
{
  TempleTile temple_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_TEMPLE, temple_tile.get_tile_description_sid());
}

