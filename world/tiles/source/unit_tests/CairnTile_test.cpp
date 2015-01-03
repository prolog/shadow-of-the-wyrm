#include "gtest/gtest.h"

TEST(SL_World_Tiles_CairnTile, type_is_TILE_TYPE_CAIRN)
{
  CairnTile cairn_tile;

  EXPECT_EQ(TileType::TILE_TYPE_CAIRN, cairn_tile.get_tile_type());
}

TEST(SL_World_Tiles_CairnTile, serialization_id)
{
  CairnTile cairn_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CAIRN_TILE, cairn_tile.get_class_identifier());
}

