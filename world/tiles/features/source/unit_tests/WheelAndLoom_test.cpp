#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_WheelAndLoom, serialization_id)
{
  WheelAndLoom w;

  EXPECT_EQ(CLASS_ID_WHEEL_AND_LOOM, w.get_class_identifier());
}

