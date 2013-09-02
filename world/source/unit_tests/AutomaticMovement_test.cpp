#include "gtest/gtest.h"

TEST(SL_World_AutomaticMovement, engaged_status)
{
  AutomaticMovement am;

  am.set_direction(DIRECTION_NORTH);
  am.set_engaged(false);

  EXPECT_FALSE(am.get_engaged());

  am.set_engaged(true);

  EXPECT_TRUE(am.get_engaged());

  am.set_direction(DIRECTION_NULL);

  EXPECT_FALSE(am.get_engaged());

  am.set_direction(DIRECTION_UP);

  EXPECT_FALSE(am.get_engaged());

  am.set_direction(DIRECTION_DOWN);

  EXPECT_FALSE(am.get_engaged());

  am.set_direction(DIRECTION_NORTH_WEST);

  EXPECT_TRUE(am.get_engaged());
}

TEST(SL_World_AutomaticMovement, serialization_id)
{
  AutomaticMovement auto_move;

  EXPECT_EQ(CLASS_ID_AUTOMATIC_MOVEMENT, auto_move.get_class_identifier());
}

TEST(SL_World_AutomaticMovement, saveload)
{
  AutomaticMovement am, am2;

  am.set_engaged(true);
  am.set_direction(DIRECTION_SOUTH_WEST);

  ostringstream oss;

  am.serialize(oss);

  istringstream iss(oss.str());

  am2.deserialize(iss);

  EXPECT_TRUE(am == am2);
}