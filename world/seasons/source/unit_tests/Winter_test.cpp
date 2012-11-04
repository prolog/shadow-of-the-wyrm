#include "gtest/gtest.h"

TEST(SL_World_Seasons_Winter, serialization_id)
{
  Winter winter;

  EXPECT_EQ(CLASS_ID_WINTER, winter.get_class_identifier());
}

