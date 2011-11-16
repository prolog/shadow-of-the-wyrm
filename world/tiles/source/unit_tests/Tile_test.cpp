#include "gtest/gtest.h"

TEST(SL_World_Tiles_Tile, set_default_properties)
{
  Tile tile;

  EXPECT_TRUE(tile.get_illuminated());
  EXPECT_FALSE(tile.get_explored());
}

TEST(SL_World_Tiles_Tile, illuminated)
{
  Tile tile;

  EXPECT_TRUE(tile.get_illuminated());
  
  tile.set_illuminated(false);

  EXPECT_FALSE(tile.get_illuminated());

  tile.set_illuminated(true);

  EXPECT_TRUE(tile.get_illuminated());
}

TEST(SL_World_Tiles_Tile, explored)
{
  Tile tile;

  EXPECT_FALSE(tile.get_explored());

  tile.set_explored(true);

  EXPECT_TRUE(tile.get_explored());

  tile.set_explored(false);

  EXPECT_FALSE(tile.get_explored());
}

TEST(SL_World_Tiles_Tile, type_is_undefined)
{
  Tile tile;

  EXPECT_EQ(TILE_TYPE_UNDEFINED, tile.get_tile_type());
}
