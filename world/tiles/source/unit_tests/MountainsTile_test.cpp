#include "gtest/gtest.h"

TEST(SL_World_Tiles_MountainsTile, type_is_TILE_TYPE_MOUNTAINS)
{
  MountainsTile mountains_tile;

  EXPECT_EQ(TILE_TYPE_MOUNTAINS, mountains_tile.get_tile_type());
}

TEST(SL_World_Tiles_MountainsTile, serialization_id)
{
  MountainsTile mountains_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MOUNTAINS_TILE, mountains_tile.get_class_identifier());
}

