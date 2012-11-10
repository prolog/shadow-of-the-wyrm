#include "gtest/gtest.h"

TEST(SL_World_Wand, serialization_id)
{
  Wand wand;

  EXPECT_EQ(CLASS_ID_WAND, wand.get_class_identifier());
}
