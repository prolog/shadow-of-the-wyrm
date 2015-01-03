#include "gtest/gtest.h"

TEST(SL_World_Tiles_RiverTile, type_is_TILE_TYPE_RIVER)
{
  RiverTile river_tile;

  EXPECT_EQ(TileType::TILE_TYPE_RIVER, river_tile.get_tile_type());
}

TEST(SL_World_Tiles_RiverTile, tile_super_type)
{
  RiverTile river_tile;

  EXPECT_EQ(TILE_SUPER_TYPE_WATER, river_tile.get_tile_super_type());
}

TEST(SL_World_Tiles_RiverTile, serialization_id)
{
  RiverTile river_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_RIVER_TILE, river_tile.get_class_identifier());
}

