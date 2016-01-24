#include "gtest/gtest.h"

TEST(SW_World_World, serialization_id)
{
  World world;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WORLD, world.get_class_identifier());
}

TEST(SW_World_World, saveload)
{
  World world, world2;
  ostringstream ss;

  world.serialize(ss);

  istringstream iss(ss.str());

  world2.deserialize(iss);

  EXPECT_TRUE(world == world2);
}
