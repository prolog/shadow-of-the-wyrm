#include "gtest/gtest.h"
#include "TileProperties.hpp"

TEST(SW_World_Tiles_BarracksTile, type_is_TILE_TYPE_BARRACKS)
{
  BarracksTile barracks_tile;

  EXPECT_EQ(TileType::TILE_TYPE_BARRACKS, barracks_tile.get_tile_type());
}

TEST(SW_World_Tiles_BarracksTile, tile_description_sid)
{
  BarracksTile barracks_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_BARRACKS, barracks_tile.get_tile_description_sid());
}

TEST(SW_World_Tiles_BarracksTile, serialization_id)
{
  BarracksTile barracks_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BARRACKS_TILE, barracks_tile.get_class_identifier());
}

TEST(SW_World_Tiles_BarracksTile, is_tile_available_for_creature)
{
  CreaturePtr c1 = std::make_shared<Creature>();
  BarracksTile bt;

  EXPECT_TRUE(bt.get_is_available_for_creature(c1));

  c1->set_race_id("cat");

  EXPECT_TRUE(bt.get_is_available_for_creature(c1));

  bt.set_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_RACES, "dog");

  EXPECT_FALSE(bt.get_is_available_for_creature(c1));

  c1->set_race_id("dog");

  EXPECT_TRUE(bt.get_is_available_for_creature(c1));
}