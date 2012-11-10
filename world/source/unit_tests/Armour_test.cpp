#include "gtest/gtest.h"

TEST(SL_World_Armour, serialization_id)
{
  Armour armour;

  EXPECT_EQ(CLASS_ID_ARMOUR, armour.get_class_identifier());
}
