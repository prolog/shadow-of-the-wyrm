#include "gtest/gtest.h"

TEST(SL_World_Tiles_WildOrchardTile, type_is_TILE_TYPE_WILD_ORCHARD)
{
  WildOrchardTile wild_orchard_tile;

  EXPECT_EQ(TileType::TILE_TYPE_WILD_ORCHARD, wild_orchard_tile.get_tile_type());
}

TEST(SL_World_Tiles_WildOrchardTile, serialization_id)
{
  WildOrchardTile wild_orchard_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WILD_ORCHARD_TILE, wild_orchard_tile.get_class_identifier());
}

