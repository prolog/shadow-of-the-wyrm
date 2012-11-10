#include "gtest/gtest.h"

TEST(SL_World_Weight, serialization_id)
{
  Weight weight;

  EXPECT_EQ(CLASS_ID_WEIGHT, weight.get_class_identifier());
}

