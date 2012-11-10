#include "gtest/gtest.h"

TEST(SL_World_Equipment, serialization_id)
{
  Equipment eq;

  EXPECT_EQ(CLASS_ID_EQUIPMENT, eq.get_class_identifier());
}
