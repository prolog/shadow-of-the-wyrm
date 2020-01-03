#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_WeatherCalculator, pct_chance_shimmer)
{
  WeatherCalculator wc;
 
  EXPECT_EQ(0, wc.calculate_pct_chance_shimmer(0));
  EXPECT_EQ(0, wc.calculate_pct_chance_shimmer(15));
  EXPECT_EQ(10, wc.calculate_pct_chance_shimmer(20));
  EXPECT_EQ(20, wc.calculate_pct_chance_shimmer(40));
  EXPECT_EQ(40, wc.calculate_pct_chance_shimmer(80));
  EXPECT_EQ(37, wc.calculate_pct_chance_shimmer(75));
  EXPECT_EQ(50, wc.calculate_pct_chance_shimmer(100));
  EXPECT_EQ(100, wc.calculate_pct_chance_shimmer(5000));
}

