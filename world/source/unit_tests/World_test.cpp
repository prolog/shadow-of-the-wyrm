#include "gtest/gtest.h"

TEST(SL_World_World, serialization_id)
{
  World world;

  EXPECT_EQ(CLASS_ID_WORLD, world.get_class_identifier());
}

