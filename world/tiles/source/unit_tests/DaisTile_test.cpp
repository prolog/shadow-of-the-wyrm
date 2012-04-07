#include "gtest/gtest.h"

TEST(SL_World_Tiles_DaisTile, type_is_TILE_TYPE_DAIS)
{
  DaisTile dais_tile;

  EXPECT_EQ(TILE_TYPE_DAIS, dais_tile.get_tile_type());
}
