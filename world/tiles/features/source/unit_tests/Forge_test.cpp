#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Forge, serialization_id)
{
  Forge f;

  EXPECT_EQ(CLASS_ID_FORGE, f.get_class_identifier());
}

