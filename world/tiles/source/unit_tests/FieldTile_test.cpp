#include "gtest/gtest.h"

TEST(SL_World_Tiles_FieldTile, type_is_TILE_TYPE_FIELD)
{
  FieldTile field_tile;

  EXPECT_EQ(TILE_TYPE_FIELD, field_tile.get_tile_type());
}
