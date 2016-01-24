#include "gtest/gtest.h"

TEST(SW_Engine_Screens_ComponentAlignment, default_override_value)
{
  ComponentAlignment ca;

  EXPECT_FALSE(ca.get_override_default());
}

