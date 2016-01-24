#include "gtest/gtest.h"

TEST(SW_World_Tiles_RockyEarthTile, type_is_TILE_TYPE_ROCKY_EARTH)
{
  RockyEarthTile rocky_tile;

  EXPECT_EQ(TileType::TILE_TYPE_ROCKY_EARTH, rocky_tile.get_tile_type());
}

TEST(SW_World_Tiles_RockyEarthTile, serialization_id)
{
  RockyEarthTile rocky_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ROCKY_EARTH_TILE, rocky_tile.get_class_identifier());
}

