#include "gtest/gtest.h"

TEST(SW_Engine_MapRegistry, serialization_id)
{
  MapRegistry mr;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAP_REGISTRY, mr.get_class_identifier());
}

