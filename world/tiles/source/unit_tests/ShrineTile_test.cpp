#include "gtest/gtest.h"

TEST(SW_World_Tiles_ShrineTile, type_is_TILE_TYPE_SHRINE)
{
  ShrineTile shrine_tile;

  EXPECT_EQ(TileType::TILE_TYPE_SHRINE, shrine_tile.get_tile_type());
}

TEST(SW_World_Tiles_ShrineTile, tile_description_sid)
{
  ShrineTile shrine_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_SHRINE, shrine_tile.get_tile_description_sid());
}

TEST(SW_World_Tiles_ShrineTile, serialization_id)
{
  ShrineTile shrine_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SHRINE_TILE, shrine_tile.get_class_identifier());
}

