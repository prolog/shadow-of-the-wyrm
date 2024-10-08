#include "gtest/gtest.h"

TEST(SW_World_Tiles_WeedsTile, type_is_TILE_TYPE_WEEDS)
{
  WeedsTile weeds_tile;

  EXPECT_EQ(TileType::TILE_TYPE_WEEDS, weeds_tile.get_tile_type());
}

TEST(SW_World_Tiles_WeedsTile, decomposes_to_field)
{
  WeedsTile weeds_tile;

  EXPECT_EQ(TileType::TILE_TYPE_FIELD, weeds_tile.get_decomposition_tile_type());
}

TEST(SW_World_Tiles_WeedsTile, serialization_id)
{
  WeedsTile weeds_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WEEDS_TILE, weeds_tile.get_class_identifier());
}

