#include "gtest/gtest.h"

TEST(SL_World_Tiles_ScrubTile, type_is_TILE_TYPE_SCRUB)
{
  ScrubTile scrub_tile;

  EXPECT_EQ(TileType::TILE_TYPE_SCRUB, scrub_tile.get_tile_type());
}


TEST(SL_World_Tiles_ScrubTile, serialization_id)
{
  ScrubTile scrub_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SCRUB_TILE, scrub_tile.get_class_identifier());
}
