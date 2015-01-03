#include "DungeonTile.hpp"
#include "gtest/gtest.h"
#include "TileGenerator.hpp"

TEST(SL_World_Tiles_Tile, correct_inventory_type)
{
  // Generally speaking, all tile super types have a usual value.
  // Items fall away from water or air, and are kept on ground tiles.
  std::map<TileSuperType, ClassIdentifier> default_st_value({{TILE_SUPER_TYPE_AIR, ClassIdentifier::CLASS_ID_NULL_INVENTORY},
                                                             {TILE_SUPER_TYPE_WATER, ClassIdentifier::CLASS_ID_NULL_INVENTORY},
                                                             {TILE_SUPER_TYPE_GROUND, ClassIdentifier::CLASS_ID_INVENTORY},
                                                             {TILE_SUPER_TYPE_UNDEFINED, ClassIdentifier::CLASS_ID_NULL_INVENTORY}});

  // But, there are exceptions.  Items fall down wells, for example.
  std::map<TileType, ClassIdentifier> tt_exceptions({{TILE_TYPE_WELL, ClassIdentifier::CLASS_ID_NULL_INVENTORY}});
  TileGenerator tg;

  for (int i = TileType::TILE_TYPE_FIRST; i < TileType::TILE_TYPE_LAST; i++)
  {
    TilePtr tile = tg.generate(static_cast<TileType>(i));

    TileType tt = tile->get_tile_type();
    TileSuperType tst = tile->get_tile_super_type();

    auto tt_it = tt_exceptions.find(tt);
    ClassIdentifier expected_value;

    if (tt_it != tt_exceptions.end())
    {
      expected_value = tt_it->second;
    }
    else
    {
      expected_value = default_st_value.find(tst)->second;
    }

    EXPECT_EQ(expected_value, tile->get_items()->get_class_identifier());
  }
}

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

  for (int i = TileType::TILE_TYPE_FIRST; i < TileType::TILE_TYPE_LAST; i++)
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
