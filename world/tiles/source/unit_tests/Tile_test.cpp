#include "Amulet.hpp"
#include "DungeonTile.hpp"
#include "gtest/gtest.h"
#include "RockTile.hpp"
#include "RockyEarthTile.hpp"
#include "TileGenerator.hpp"

TEST(SW_World_Tiles_Tile, correct_inventory_type)
{
  // Generally speaking, all tile super types have a usual value.
  // Items fall away from water or air, and are kept on ground tiles.
  std::map<TileSuperType, ClassIdentifier> default_st_value({{TileSuperType::TILE_SUPER_TYPE_AIR, ClassIdentifier::CLASS_ID_NULL_INVENTORY},
                                                             {TileSuperType::TILE_SUPER_TYPE_WATER, ClassIdentifier::CLASS_ID_NULL_INVENTORY},
                                                             {TileSuperType::TILE_SUPER_TYPE_GROUND, ClassIdentifier::CLASS_ID_INVENTORY},
                                                             {TileSuperType::TILE_SUPER_TYPE_UNDEFINED, ClassIdentifier::CLASS_ID_NULL_INVENTORY}});

  // But, there are exceptions.  Items fall down wells, for example.
  // And things normally "drop through" water except when we're at the
  // bottom of an ocean, or in a patch of aquatic vegetation.
  std::map<TileType, ClassIdentifier> tt_exceptions({{TileType::TILE_TYPE_WELL, ClassIdentifier::CLASS_ID_NULL_INVENTORY},
                                                     {TileType::TILE_TYPE_ROCK, ClassIdentifier::CLASS_ID_NULL_INVENTORY},
                                                     {TileType::TILE_TYPE_EARTH, ClassIdentifier::CLASS_ID_NULL_INVENTORY},
                                                     {TileType::TILE_TYPE_SEABED, ClassIdentifier::CLASS_ID_INVENTORY},
                                                     {TileType::TILE_TYPE_AQUATIC_VEGETATION, ClassIdentifier::CLASS_ID_INVENTORY}});
  TileGenerator tg;

  for (int i = static_cast<int>(TileType::TILE_TYPE_FIRST); i < static_cast<int>(TileType::TILE_TYPE_LAST); i++)
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

// Ensure that when a tile is transformed from a tile with a null inventory,
// that the null inventory is not carried over from the old tile.
TEST(SW_World_Tiles_Tile, transform_from_solid_rock_inventory)
{
  TilePtr rock_tile = std::make_shared<RockTile>();
  TilePtr earth_tile = std::make_shared<RockyEarthTile>();

  earth_tile->transform_from(rock_tile);
  
  ItemPtr amulet = std::make_shared<Amulet>();
  earth_tile->get_items()->add_front(amulet);

  EXPECT_EQ(1, earth_tile->get_items()->count_items());
}

TEST(SW_World_Tiles_Tile, extra_desc_sids)
{
  DungeonTile tile;

  tile.set_additional_property("PROPERTY1", "123");
  tile.set_additional_property("PROPERTY_EXTRA_DESCRIPTION", "123");
  tile.set_additional_property("PROPERTY1_EXTRA_DESCRIPTION_MORETEXTHERE", "123");
  tile.set_additional_property("PROPERTY1_NOTEXTRA_DESC_RIPTION", "123");
  tile.set_additional_property("PROPERTY17", "123");
  tile.set_additional_property("PROPERTY11", "123");
  tile.set_additional_property("PROPERTY22", "123");

  EXPECT_EQ(2, tile.get_extra_description_sids().size());
}

TEST(SW_World_Tiles_Tile, set_default_properties)
{
  DungeonTile tile;

  EXPECT_TRUE(tile.get_illuminated());
  EXPECT_FALSE(tile.get_explored());
}

TEST(SW_World_Tiles_Tile, illuminated)
{
  DungeonTile tile;

  EXPECT_TRUE(tile.get_illuminated());
  
  tile.set_illuminated(false);

  EXPECT_FALSE(tile.get_illuminated());

  tile.set_illuminated(true);

  EXPECT_TRUE(tile.get_illuminated());
}

TEST(SW_World_Tiles_Tile, has_race_restrictions)
{
  DungeonTile dt;

  EXPECT_FALSE(dt.has_race_restrictions());

  dt.set_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_RACES, "trash_panda");

  EXPECT_TRUE(dt.has_race_restrictions());
}

TEST(SW_World_Tiles_Tile, is_race_allowed)
{
  DungeonTile dt;

  EXPECT_TRUE(dt.is_race_allowed("some_race"));
  EXPECT_TRUE(dt.is_race_allowed("some_other_race_since_there_are_no_restrictions_yet"));

  dt.set_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_RACES, "trash_panda");

  EXPECT_FALSE(dt.is_race_allowed("some_race"));
  EXPECT_TRUE(dt.is_race_allowed("trash_panda"));
}

TEST(SW_World_Tiles_Tile, has_creature_id_restrictions)
{
  DungeonTile dt;

  EXPECT_FALSE(dt.has_creature_id_restrictions());

  dt.set_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_CREATURE_IDS, "abc123,def456");

  EXPECT_TRUE(dt.has_creature_id_restrictions());
}

TEST(SW_World_Tiles_Tile, is_creature_id_allowed)
{
  DungeonTile dt;

  EXPECT_TRUE(dt.is_creature_id_allowed("some_cr_id"));
  EXPECT_TRUE(dt.is_creature_id_allowed("some_other_creature_since_there_are_no_restrictions_yet"));

  dt.set_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_CREATURE_IDS, "abc,def");

  EXPECT_FALSE(dt.is_creature_id_allowed("ghi"));
  EXPECT_TRUE(dt.is_creature_id_allowed("def"));
}

TEST(SW_World_Tiles_Tile, explored)
{
  DungeonTile tile;

  EXPECT_FALSE(tile.get_explored());

  tile.set_explored(true);

  EXPECT_TRUE(tile.get_explored());

  tile.set_explored(false);

  EXPECT_FALSE(tile.get_explored());
}

TEST(SW_World_Tiles_Tile, saveload)
{
  TileGenerator tg;

  for (int i = static_cast<int>(TileType::TILE_TYPE_FIRST); i < static_cast<int>(TileType::TILE_TYPE_LAST); i++)
  {
    TilePtr tp = tg.generate(static_cast<TileType>(i));
    MapExitPtr me = MapFactory::create_map_exit();
    me->set_map_id("foobar");
    TileExitMap& tem = tp->get_tile_exit_map_ref();
    tem[Direction::DIRECTION_UP] = me;

    TilePtr tp2 = tg.generate(static_cast<TileType>(i));

    ostringstream ss;

    tp->serialize(ss);

    istringstream iss(ss.str());

    tp2->deserialize(iss);

    EXPECT_TRUE(*tp == *tp2);

    if (!(*tp == *tp2))
    {
      cout << "Failed for tile type: " << i;
    }
  }
}
