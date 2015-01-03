#include "gtest/gtest.h"

TEST(SL_World_Tiles_DungeonComplexTile, type_is_TILE_TYPE_DUNGEON_COMPLEX)
{
  DungeonComplexTile dungeon_complex_tile;

  EXPECT_EQ(TileType::TILE_TYPE_DUNGEON_COMPLEX, dungeon_complex_tile.get_tile_type());
}

TEST(SL_World_Tiles_DungeonComplexTile, tile_description_sid)
{
  DungeonComplexTile dungeon_complex_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_DUNGEON_COMPLEX, dungeon_complex_tile.get_tile_description_sid());
}

TEST(SL_World_Tiles_DungeonComplexTile, serialization_id)
{
  DungeonComplexTile dungeon_complex_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DUNGEON_COMPLEX_TILE, dungeon_complex_tile.get_class_identifier());
}


