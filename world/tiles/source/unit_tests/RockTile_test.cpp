#include "gtest/gtest.h"

TEST(SL_World_Tiles_RockTile, type_is_TILE_TYPE_ROCK)
{
  RockTile rock_tile;

  EXPECT_EQ(TILE_TYPE_ROCK, rock_tile.get_tile_type());
}

TEST(SL_World_Tiles_RockTile, serialization_id)
{
  RockTile rock_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ROCK_TILE, rock_tile.get_class_identifier());
}

