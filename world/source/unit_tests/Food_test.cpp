#include "gtest/gtest.h"

TEST(SL_World_Food, serialization_id)
{
  Food food;

  EXPECT_EQ(CLASS_ID_FOOD, food.get_class_identifier());
}
