#include "gtest/gtest.h"

TEST(SW_World_Tiles_SeabedTile, type_is_TILE_TYPE_SEABED)
{
  SeabedTile seabed_tile;

  EXPECT_EQ(TileType::TILE_TYPE_SEABED, seabed_tile.get_tile_type());
}

TEST(SW_World_Tiles_SeabedTile, tile_super_type)
{
  SeabedTile seabed_tile;

  EXPECT_EQ(TileSuperType::TILE_SUPER_TYPE_WATER, seabed_tile.get_tile_super_type());
}

TEST(SW_World_Tiles_SeabedTile, serialization_id)
{
  SeabedTile seabed_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SEABED_TILE, seabed_tile.get_class_identifier());
}

