#include "gtest/gtest.h"

TEST(SL_World_MovementAccumulation, serialization_id)
{
  MovementAccumulation ma;

  EXPECT_EQ(CLASS_ID_MOVEMENT_ACCUMULATION, ma.get_class_identifier());
}
