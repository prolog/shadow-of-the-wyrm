#include "gtest/gtest.h"

TEST(SW_World_Tiles_IceTile, non_blocking_with_null_creature)
{
  IceTile ice_tile;
  EXPECT_FALSE(ice_tile.get_is_blocking(nullptr));
}

TEST(SW_World_Tiles_IceTile, type_is_TILE_TYPE_ICE)
{
  IceTile ice_tile;

  EXPECT_EQ(TileType::TILE_TYPE_ICE, ice_tile.get_tile_type());
}

TEST(SW_World_Tiles_IceTile, serialization_id)
{
  IceTile ice_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ICE_TILE, ice_tile.get_class_identifier());
}

