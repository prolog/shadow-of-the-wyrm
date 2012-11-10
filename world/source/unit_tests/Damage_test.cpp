#include "gtest/gtest.h"

TEST(SL_World_Damage, serialization_id)
{
  Damage damage;

  EXPECT_EQ(CLASS_ID_DAMAGE, damage.get_class_identifier());
}

