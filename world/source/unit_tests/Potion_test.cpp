#include "gtest/gtest.h"

TEST(SL_World_Potion, serialization_id)
{
  Potion potion;

  EXPECT_EQ(CLASS_ID_POTION, potion.get_class_identifier());
}
