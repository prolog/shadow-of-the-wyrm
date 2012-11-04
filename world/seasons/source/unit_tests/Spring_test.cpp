#include "gtest/gtest.h"

TEST(SL_World_Seasons_Spring, serialization_id)
{
  Spring spring;

  EXPECT_EQ(CLASS_ID_SPRING, spring.get_class_identifier());
}

