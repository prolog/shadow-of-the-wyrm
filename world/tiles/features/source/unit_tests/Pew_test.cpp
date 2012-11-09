#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Pew, serialization_id)
{
  Pew pew;

  EXPECT_EQ(CLASS_ID_PEW, pew.get_class_identifier());
}

