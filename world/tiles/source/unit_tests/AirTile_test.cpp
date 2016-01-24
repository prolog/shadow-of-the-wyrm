#include "gtest/gtest.h"

TEST(SW_World_Tiles_AirTile, type_is_TILE_TYPE_AIR)
{
  AirTile air_tile;

  EXPECT_EQ(TileType::TILE_TYPE_AIR, air_tile.get_tile_type());
}

TEST(SW_World_Tiles_AirTile, tile_super_type)
{
  AirTile air_tile;
  
  EXPECT_EQ(TileSuperType::TILE_SUPER_TYPE_AIR, air_tile.get_tile_super_type());
}

TEST(SW_World_Tiles_AirTile, serialization_id)
{
  AirTile air_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AIR_TILE, air_tile.get_class_identifier());
}

