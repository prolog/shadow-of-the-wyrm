#include "gtest/gtest.h"

TEST(SL_World_Tiles_DaisTile, type_is_TILE_TYPE_DAIS)
{
  DaisTile dais_tile;

  EXPECT_EQ(TILE_TYPE_DAIS, dais_tile.get_tile_type());
}

TEST(SL_World_Tiles_DaisTile, serialization_id)
{
  DaisTile dais_tile;

  EXPECT_EQ(CLASS_ID_DAIS_TILE, dais_tile.get_class_identifier());
}

