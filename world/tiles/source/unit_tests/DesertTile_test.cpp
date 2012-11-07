#include "gtest/gtest.h"

TEST(SL_World_Tiles_DesertTile, type_is_TILE_TYPE_DESERT)
{
  DesertTile desert_tile;
  
  EXPECT_EQ(TILE_TYPE_DESERT, desert_tile.get_tile_type());  
}

TEST(SL_World_Tiles_DesertTile, serialization_id)
{
  DesertTile desert_tile;

  EXPECT_EQ(CLASS_ID_DESERT_TILE, desert_tile.get_class_identifier());
}

