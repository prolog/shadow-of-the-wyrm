#include "DungeonTile.hpp"
#include "gtest/gtest.h"

TEST(SL_World_Tiles_Tile, set_default_properties)
{
  DungeonTile tile;

  EXPECT_TRUE(tile.get_illuminated());
  EXPECT_FALSE(tile.get_explored());
}

TEST(SL_World_Tiles_Tile, illuminated)
{
  DungeonTile tile;

  EXPECT_TRUE(tile.get_illuminated());
  
  tile.set_illuminated(false);

  EXPECT_FALSE(tile.get_illuminated());

  tile.set_illuminated(true);

  EXPECT_TRUE(tile.get_illuminated());
}

TEST(SL_World_Tiles_Tile, explored)
{
  DungeonTile tile;

  EXPECT_FALSE(tile.get_explored());

  tile.set_explored(true);

  EXPECT_TRUE(tile.get_explored());

  tile.set_explored(false);

  EXPECT_FALSE(tile.get_explored());
}

