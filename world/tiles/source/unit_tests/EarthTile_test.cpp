#include "gtest/gtest.h"

TEST(SW_World_Tiles_EarthTile, type_is_TILE_TYPE_EARTH)
{
  EarthTile earth_tile;

  EXPECT_EQ(TileType::TILE_TYPE_EARTH, earth_tile.get_tile_type());
}

TEST(SW_World_Tiles_EarthTile, serialization_id)
{
  EarthTile earth_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_EARTH_TILE, earth_tile.get_class_identifier());
}

