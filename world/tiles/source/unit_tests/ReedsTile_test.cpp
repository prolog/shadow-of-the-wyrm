#include "gtest/gtest.h"

TEST(SL_World_Tiles_ReedsTile, type_is_TILE_TYPE_REEDS)
{
  ReedsTile reeds_tile;

  EXPECT_EQ(TileType::TILE_TYPE_REEDS, reeds_tile.get_tile_type());
}

TEST(SL_World_Tiles_ReedsTile, serialization_id)
{
  ReedsTile reeds_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_REEDS_TILE, reeds_tile.get_class_identifier());
}
