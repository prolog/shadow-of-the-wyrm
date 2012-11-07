#include "gtest/gtest.h"

TEST(SL_World_Tiles_HillsTile, type_is_TILE_TYPE_HILLS)
{
  HillsTile hills_tile;

  EXPECT_EQ(TILE_TYPE_HILLS, hills_tile.get_tile_type());
}

TEST(SL_World_Tiles_HillsTile, serialization_id)
{
  HillsTile hills_tile;

  EXPECT_EQ(CLASS_ID_HILLS_TILE, hills_tile.get_class_identifier());
}
