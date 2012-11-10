#include "gtest/gtest.h"

TEST(SL_World_Boat, serialization_id)
{
  Boat boat;

  EXPECT_EQ(CLASS_ID_BOAT, boat.get_class_identifier());
}
