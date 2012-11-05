#include "gtest/gtest.h"

TEST(SL_Engine_MapRegistry, serialization_id)
{
  MapRegistry mr;

  EXPECT_EQ(CLASS_ID_MAP_REGISTRY, mr.get_class_identifier());
}

