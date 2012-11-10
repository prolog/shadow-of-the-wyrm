#include "gtest/gtest.h"

TEST(SL_World_Ammunition, serialization_id)
{
  Ammunition ammo;

  EXPECT_EQ(CLASS_ID_AMMUNITION, ammo.get_class_identifier());
}
