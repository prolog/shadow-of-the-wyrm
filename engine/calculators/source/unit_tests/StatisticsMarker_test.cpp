#include "gtest/gtest.h"

class SW_Engine_Calculators_StatisticsMarkerFixture : public ::testing::Test
{
  public:
    int calculate_mark_probability_denominator(const int stat_base_value);

  protected:
    StatisticsMarker sm;
};

int SW_Engine_Calculators_StatisticsMarkerFixture::calculate_mark_probability_denominator(const int stat_base_value)
{
  return sm.calculate_mark_probability_denominator(stat_base_value);
}

TEST_F(SW_Engine_Calculators_StatisticsMarkerFixture, calc_mark_denom)
{
  EXPECT_EQ(1, calculate_mark_probability_denominator(-500));
  EXPECT_EQ(1, calculate_mark_probability_denominator(-2));
  EXPECT_EQ(1, calculate_mark_probability_denominator(5));
  EXPECT_EQ(2, calculate_mark_probability_denominator(11));
  EXPECT_EQ(4, calculate_mark_probability_denominator(24));
  EXPECT_EQ(8, calculate_mark_probability_denominator(33));
  EXPECT_EQ(16, calculate_mark_probability_denominator(47));
  EXPECT_EQ(32, calculate_mark_probability_denominator(57));
  EXPECT_EQ(64, calculate_mark_probability_denominator(68));
  EXPECT_EQ(128, calculate_mark_probability_denominator(70));
  EXPECT_EQ(256, calculate_mark_probability_denominator(82));
  EXPECT_EQ(512, calculate_mark_probability_denominator(99));
}