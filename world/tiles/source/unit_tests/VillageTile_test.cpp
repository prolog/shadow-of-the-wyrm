#include "gtest/gtest.h"

TEST(SL_World_Tiles_VillageTile, type_is_TILE_TYPE_VILLAGE)
{
  VillageTile village_tile;

  EXPECT_EQ(TileType::TILE_TYPE_VILLAGE, village_tile.get_tile_type());
}

TEST(SL_World_Tiles_VillageTile, settlement_type)
{
  VillageTile village_tile;

  for (int i = static_cast<int>(SettlementType::SETTLEMENT_TYPE_ORDERLY_VILLAGE); i < static_cast<int>(SettlementType::SETTLEMENT_TYPE_MAX); i++)
  {
    SettlementType st = static_cast<SettlementType>(i);
    village_tile.set_settlement_type(st);

    EXPECT_EQ(st, village_tile.get_settlement_type()); 
  }
}

TEST(SL_World_Tiles_VillageTile, village_race)
{
  VillageTile village_tile;

  village_tile.set_village_race_id("robot_monkeys");

  EXPECT_EQ("robot_monkeys", village_tile.get_village_race_id());
}

TEST(SL_World_Tiles_VillageTile, serialization_id)
{
  VillageTile village_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_VILLAGE_TILE, village_tile.get_class_identifier());
}

