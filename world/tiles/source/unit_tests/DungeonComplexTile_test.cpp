#include "gtest/gtest.h"

TEST(SL_World_Tiles_DungeonComplexTile, type_is_TILE_TYPE_DUNGEON_COMPLEX)
{
  DungeonComplexTile castle_tile;

  EXPECT_EQ(TILE_TYPE_DUNGEON_COMPLEX, castle_tile.get_tile_type());
}

TEST(SL_World_Tiles_DungeonComplexTile, tile_description_sid)
{
  DungeonComplexTile castle_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_DUNGEON_COMPLEX, castle_tile.get_tile_description_sid());
}

