#include "DungeonTile.hpp"
#include "gtest/gtest.h"
#include "TileGenerator.hpp"

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

TEST(SL_World_Tiles_Tile, saveload)
{
  TileGenerator tg;

  for (int i = TILE_TYPE_FIRST; i < TILE_TYPE_LAST; i++)
  {
    TilePtr tp = tg.generate(static_cast<TileType>(i));
    MapExitPtr me = MapFactory::create_map_exit();
    me->set_map_id("foobar");
    TileExitMap& tem = tp->get_tile_exit_map_ref();
    tem[DIRECTION_UP] = me;

    TilePtr tp2 = tg.generate(static_cast<TileType>(i));

    ostringstream ss;

    tp->serialize(ss);

    istringstream iss(ss.str());

    tp2->deserialize(iss);

    EXPECT_TRUE(*tp == *tp2);
  }
}
