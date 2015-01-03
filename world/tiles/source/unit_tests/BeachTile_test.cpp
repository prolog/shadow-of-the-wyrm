#include "gtest/gtest.h"

TEST(SL_World_Tiles_BeachTile, type_is_TILE_TYPE_BEACH)
{
  BeachTile beach_tile;

  EXPECT_EQ(TILE_TYPE_BEACH, beach_tile.get_tile_type());
}

TEST(SL_World_Tiles_BeachTile, serialization_id)
{
  BeachTile beach_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BEACH_TILE, beach_tile.get_class_identifier());
}
