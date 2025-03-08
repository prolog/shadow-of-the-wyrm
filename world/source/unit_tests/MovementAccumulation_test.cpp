#include "gtest/gtest.h"

MovementAccumulation setup_ma();

MovementAccumulation setup_ma()
{
  MovementAccumulation ma;
  
  ma.set_minutes_on_super_type_given_movement(12);
  ma.set_minutes_on_tile_type_given_movement(8);
  ma.set_movement_type(MovementType::MOVEMENT_TYPE_FLYING);
  ma.set_tile_frozen(false);
  ma.set_tile_super_type(TileSuperType::TILE_SUPER_TYPE_AIR);
  ma.set_tile_type(TileType::TILE_TYPE_AIR);

  return ma;
}

TEST(SW_World_MovementAccumulation, reset)
{
  MovementAccumulation ma = setup_ma();
  ma.reset();

  EXPECT_EQ(0, ma.get_minutes_on_super_type_given_movement());
  EXPECT_EQ(0, ma.get_minutes_on_tile_type_given_movement());
  EXPECT_EQ(MovementType::MOVEMENT_TYPE_WALKING, ma.get_movement_type());
  EXPECT_EQ(false, ma.get_tile_frozen());
  EXPECT_EQ(TileSuperType::TILE_SUPER_TYPE_UNDEFINED, ma.get_tile_super_type());
  EXPECT_EQ(TileType::TILE_TYPE_UNDEFINED, ma.get_tile_type());
}

TEST(SW_World_MovementAccumulation, reset_minutes)
{
  MovementAccumulation ma = setup_ma();
  ma.reset_minutes();

  EXPECT_EQ(0, ma.get_minutes_on_super_type_given_movement());
  EXPECT_EQ(0, ma.get_minutes_on_tile_type_given_movement());
  EXPECT_EQ(MovementType::MOVEMENT_TYPE_FLYING, ma.get_movement_type());
  EXPECT_EQ(false, ma.get_tile_frozen());
  EXPECT_EQ(TileSuperType::TILE_SUPER_TYPE_AIR, ma.get_tile_super_type());
  EXPECT_EQ(TileType::TILE_TYPE_AIR, ma.get_tile_type());
}

TEST(SW_World_MovementAccumulation, serialization_id)
{
  MovementAccumulation ma;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MOVEMENT_ACCUMULATION, ma.get_class_identifier());
}

TEST(SW_World_MovementAccumulation, saveload)
{
  MovementAccumulation ma, ma2;

  ma.set_movement_type(MovementType::MOVEMENT_TYPE_BOAT);
  ma.set_minutes_on_super_type_given_movement(123);
  ma.set_tile_super_type(TileSuperType::TILE_SUPER_TYPE_WATER);
  ma.set_minutes_on_tile_type_given_movement(321);
  ma.set_tile_type(TileType::TILE_TYPE_SEA);

  ostringstream ss;

  ma.serialize(ss);

  istringstream iss(ss.str());

  ma2.deserialize(iss);

  EXPECT_TRUE(ma == ma2);
}
