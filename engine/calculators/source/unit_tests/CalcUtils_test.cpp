#include "gtest/gtest.h"

TEST(SL_World_Calculators_CalcUtils, pct_val)
{
  EXPECT_EQ(0, CalcUtils::pct_val(-15));
  EXPECT_EQ(0, CalcUtils::pct_val(0));
  EXPECT_EQ(1, CalcUtils::pct_val(1));
  EXPECT_EQ(37, CalcUtils::pct_val(37));
  EXPECT_EQ(99, CalcUtils::pct_val(99));
  EXPECT_EQ(100, CalcUtils::pct_val(100));
  EXPECT_EQ(100, CalcUtils::pct_val(5672));
}

