#include "gtest/gtest.h"

TEST(SL_World_MovementAccumulation, serialization_id)
{
  MovementAccumulation ma;

  EXPECT_EQ(CLASS_ID_MOVEMENT_ACCUMULATION, ma.get_class_identifier());
}

TEST(SL_World_MovementAccumulation, saveload)
{
  MovementAccumulation ma, ma2;

  ma.set_movement_type(MOVEMENT_TYPE_BOAT);
  ma.set_minutes_on_super_type_given_movement(123);
  ma.set_tile_super_type(TILE_SUPER_TYPE_WATER);
  ma.set_minutes_on_tile_type_given_movement(321);
  ma.set_tile_type(TILE_TYPE_SEA);

  ostringstream ss;

  ma.serialize(ss);

  istringstream iss(ss.str());

  ma2.deserialize(iss);

  EXPECT_TRUE(ma == ma2);
}
