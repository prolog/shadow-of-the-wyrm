#include "gtest/gtest.h"

TEST(SW_World_Tiles_GraveTile, type_is_TILE_TYPE_GRAVE)
{
  GraveTile grave_tile;

  EXPECT_EQ(TileType::TILE_TYPE_GRAVE, grave_tile.get_tile_type());
}

TEST(SW_World_Tiles_GraveTile, serialization_id)
{
  GraveTile grave_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_GRAVE_TILE, grave_tile.get_class_identifier());
}

