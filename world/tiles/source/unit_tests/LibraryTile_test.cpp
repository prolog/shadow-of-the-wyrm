#include "gtest/gtest.h"

TEST(SL_World_Tiles_LibraryTile, type_is_TILE_TYPE_LIBRARY)
{
  LibraryTile library_tile;

  EXPECT_EQ(TILE_TYPE_LIBRARY, library_tile.get_tile_type());
}

TEST(SL_World_Tiles_LibraryTile, tile_description_sid)
{
  LibraryTile library_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_LIBRARY, library_tile.get_tile_description_sid());
}

