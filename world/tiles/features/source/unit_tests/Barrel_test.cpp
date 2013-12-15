#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Barrel, serialization_id)
{
  Barrel barrel;

  EXPECT_EQ(CLASS_ID_BARREL, barrel.get_class_identifier());
}

