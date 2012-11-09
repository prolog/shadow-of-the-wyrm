#include "gtest/gtest.h"

TEST(SL_World_Tiles_Feature_Bench, serialization_id)
{
  Bench bench;

  EXPECT_EQ(CLASS_ID_BENCH, bench.get_class_identifier());
}

