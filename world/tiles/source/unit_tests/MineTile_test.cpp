#include "gtest/gtest.h"

TEST(SL_World_Tiles_MineTile, type_is_TILE_TYPE_MINE)
{
  MineTile mine_tile;

  EXPECT_EQ(TileType::TILE_TYPE_MINE, mine_tile.get_tile_type());
}

TEST(SL_World_Tiles_MineTile, tile_description_sid)
{
  MineTile mine_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_MINE, mine_tile.get_tile_description_sid());
}

TEST(SL_World_Tiles_MineTile, serialization_id)
{
  MineTile mine_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MINE_TILE, mine_tile.get_class_identifier());
}


