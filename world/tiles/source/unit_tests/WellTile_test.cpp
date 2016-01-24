#include "gtest/gtest.h"

TEST(SW_World_Tiles_WellTile, type_is_TILE_TYPE_WELL)
{
  WellTile well_tile;

  EXPECT_EQ(TileType::TILE_TYPE_WELL, well_tile.get_tile_type());
}

TEST(SW_World_Tiles_WellTile, serialization_id)
{
  WellTile well_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WELL_TILE, well_tile.get_class_identifier());
}

