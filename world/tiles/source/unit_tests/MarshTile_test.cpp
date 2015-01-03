#include "gtest/gtest.h"

TEST(SL_World_Tiles_MarshTile, type_is_TILE_TYPE_MARSH)
{
  MarshTile marsh_tile;

  EXPECT_EQ(TileType::TILE_TYPE_MARSH, marsh_tile.get_tile_type());
}

TEST(SL_World_Tiles_MarshTile, serialization_id)
{
  MarshTile marsh_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MARSH_TILE, marsh_tile.get_class_identifier());
}

