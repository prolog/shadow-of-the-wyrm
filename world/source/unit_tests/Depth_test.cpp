#include "gtest/gtest.h"

TEST(SL_World_Depth, serialization_id)
{
  Depth depth;

  EXPECT_EQ(CLASS_ID_DEPTH, depth.get_class_identifier());
}

