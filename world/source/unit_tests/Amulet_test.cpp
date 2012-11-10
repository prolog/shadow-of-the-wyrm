#include "gtest/gtest.h"

TEST(SL_World_Amulet, serialization_id)
{
  Amulet amulet;

  EXPECT_EQ(CLASS_ID_AMULET, amulet.get_class_identifier());
}
