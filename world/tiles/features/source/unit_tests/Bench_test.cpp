#include "gtest/gtest.h"

TEST(SW_World_Tiles_Feature_Bench, serialization_id)
{
  Bench bench;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BENCH, bench.get_class_identifier());
}

