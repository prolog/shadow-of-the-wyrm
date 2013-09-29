#include "gtest/gtest.h"

TEST(SL_World_Tiles_WellTile, type_is_TILE_TYPE_WELL)
{
  WellTile pier_tile;

  EXPECT_EQ(TILE_TYPE_WELL, pier_tile.get_tile_type());
}

TEST(SL_World_Tiles_WellTile, serialization_id)
{
  WellTile pier_tile;

  EXPECT_EQ(CLASS_ID_WELL_TILE, pier_tile.get_class_identifier());
}

