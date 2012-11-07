#include "gtest/gtest.h"

TEST(SL_World_Tiles_SpringsTile, type_is_TILE_TYPE_SPRINGS)
{
  SpringsTile springs_tile;

  EXPECT_EQ(TILE_TYPE_SPRINGS, springs_tile.get_tile_type());
}

TEST(SL_World_Tiles_SpringsTile, serialization_id)
{
  SpringsTile springs_tile;

  EXPECT_EQ(CLASS_ID_SPRINGS_TILE, springs_tile.get_class_identifier());
}

