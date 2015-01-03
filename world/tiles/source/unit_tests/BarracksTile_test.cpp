#include "gtest/gtest.h"

TEST(SL_World_Tiles_BarracksTile, type_is_TILE_TYPE_BARRACKS)
{
  BarracksTile barracks_tile;

  EXPECT_EQ(TILE_TYPE_BARRACKS, barracks_tile.get_tile_type());
}

TEST(SL_World_Tiles_BarracksTile, tile_description_sid)
{
  BarracksTile barracks_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_BARRACKS, barracks_tile.get_tile_description_sid());
}

TEST(SL_World_Tiles_BarracksTile, serialization_id)
{
  BarracksTile barracks_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BARRACKS_TILE, barracks_tile.get_class_identifier());
}

