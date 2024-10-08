#include "gtest/gtest.h"

TEST(SW_World_Tiles_BushTile, type_is_TILE_TYPE_BUSH)
{
  BushTile bush_tile;

  EXPECT_EQ(TileType::TILE_TYPE_BUSH, bush_tile.get_tile_type());
}

TEST(SW_World_Tiles_BushTile, decomposes_to_field)
{
  BushTile bush_tile;

  EXPECT_EQ(TileType::TILE_TYPE_FIELD, bush_tile.get_decomposition_tile_type());
}