#include "gtest/gtest.h"

TEST(SL_World_Seasons_Summer, serialization_id)
{
  Summer summer;

  EXPECT_EQ(CLASS_ID_SUMMER, summer.get_class_identifier());
}

