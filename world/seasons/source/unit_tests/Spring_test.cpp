#include "gtest/gtest.h"

TEST(SL_World_Seasons_Spring, serialization_id)
{
  Spring spring;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SPRING, spring.get_class_identifier());
}

TEST(SL_World_Seasons_Spring, saveload)
{
  Spring spring, spring2;

  ostringstream ss;

  spring.serialize(ss);

  istringstream iss(ss.str());

  spring2.deserialize(iss);

  EXPECT_TRUE(spring == spring2);
}

