#include "gtest/gtest.h"

TEST(SW_World_Tiles_SewerTile, type_is_TILE_TYPE_SEWER)
{
  SewerTile sewer_tile;

  EXPECT_EQ(TileType::TILE_TYPE_SEWER, sewer_tile.get_tile_type());
}

TEST(SW_World_Tiles_SewerTile, serialization_id)
{
  SewerTile sewer_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SEWER_TILE, sewer_tile.get_class_identifier());
}

