#include "gtest/gtest.h"

TEST(SL_World_Seasons_Summer, serialization_id)
{
  Summer summer;

  EXPECT_EQ(CLASS_ID_SUMMER, summer.get_class_identifier());
}

TEST(SL_World_Seasons_Summer, saveload)
{
  Summer summer, summer2;

  ostringstream ss;

  summer.serialize(ss);

  istringstream iss(ss.str());

  summer2.deserialize(iss);

  EXPECT_TRUE(summer == summer2);
}

