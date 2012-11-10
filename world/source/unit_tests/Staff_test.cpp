#include "gtest/gtest.h"

TEST(SL_World_Staff, serialization_id)
{
  Staff staff;

  EXPECT_EQ(CLASS_ID_STAFF, staff.get_class_identifier());
}
