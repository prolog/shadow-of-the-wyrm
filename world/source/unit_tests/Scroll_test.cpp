#include "gtest/gtest.h"

TEST(SL_World_Scroll, serialization_id)
{
  Scroll scroll;

  EXPECT_EQ(CLASS_ID_SCROLL, scroll.get_class_identifier());
}
