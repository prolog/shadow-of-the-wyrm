#include "gtest/gtest.h"

TEST(SL_World_Tiles_DungeonTile, type_is_TILE_TYPE_DUNGEON)
{
  DungeonTile dungeon_tile;

  EXPECT_EQ(TILE_TYPE_DUNGEON, dungeon_tile.get_tile_type());
}
