#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_WheelAndLoom, serialization_id)
{
  WheelAndLoom w;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM, w.get_class_identifier());
}

