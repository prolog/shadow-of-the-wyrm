#include "gtest/gtest.h"

TEST(SL_World_Tiles_AirTile, type_is_TILE_TYPE_AIR)
{
  AirTile air_tile;

  EXPECT_EQ(TILE_TYPE_AIR, air_tile.get_tile_type());
}

TEST(SL_World_Tiles_AirTile, tile_super_type)
{
  AirTile air_tile;
  
  EXPECT_EQ(TILE_SUPER_TYPE_AIR, air_tile.get_tile_super_type());
}

TEST(SL_World_Tiles_AirTile, serialization_id)
{
  AirTile air_tile;

  EXPECT_EQ(CLASS_ID_AIR_TILE, air_tile.get_class_identifier());
}

