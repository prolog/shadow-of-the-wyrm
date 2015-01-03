#include "gtest/gtest.h"

TEST(SL_World_Tiles_PierTile, type_is_TILE_TYPE_PIER)
{
  PierTile pier_tile;

  EXPECT_EQ(TileType::TILE_TYPE_PIER, pier_tile.get_tile_type());
}

TEST(SL_World_Tiles_PierTile, serialization_id)
{
  PierTile pier_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PIER_TILE, pier_tile.get_class_identifier());
}

