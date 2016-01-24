#include "gtest/gtest.h"

TEST(SW_Engine_Actions_AutomaticMovementFlags, flag_values)
{
  AutomaticMovementFlags af1(true, false, true, false);
  AutomaticMovementFlags af2(false, true, false, true);

  EXPECT_TRUE(af1.get_ignore_items());
  EXPECT_FALSE(af2.get_ignore_items());

  EXPECT_FALSE(af1.get_ignore_tile());
  EXPECT_TRUE(af2.get_ignore_tile());

  EXPECT_TRUE(af1.get_ignore_prev_visited());
  EXPECT_FALSE(af2.get_ignore_prev_visited());

  EXPECT_FALSE(af1.get_ignore_feature());
  EXPECT_TRUE(af2.get_ignore_feature());
}


