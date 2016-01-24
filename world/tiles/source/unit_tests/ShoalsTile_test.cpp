#include "gtest/gtest.h"

TEST(SW_World_Tiles_ShoalsTile, type_is_TILE_TYPE_SHOALS)
{
  ShoalsTile shoals_tile;

  EXPECT_EQ(TileType::TILE_TYPE_SHOALS, shoals_tile.get_tile_type());
}

TEST(SW_World_Tiles_ShoalsTile, serialization_id)
{
  ShoalsTile shoals_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SHOALS_TILE, shoals_tile.get_class_identifier());
}

