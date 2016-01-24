#include "gtest/gtest.h"

class SW_Engine_Effects_ModifyStatisticsEffect : public ::testing::Test
{
  public:
    int get_primary_statistic_modifier(const int stat_score, const int stat_mod);
};

int SW_Engine_Effects_ModifyStatisticsEffect::get_primary_statistic_modifier(const int stat_score, const int stat_mod)
{
  ModifyStatisticsEffect mse;

  return mse.get_primary_statistic_modifier(stat_score, stat_mod);
}

TEST_F(SW_Engine_Effects_ModifyStatisticsEffect, get_primary_stat_modifier)
{
  EXPECT_EQ(4, get_primary_statistic_modifier(12, 4));

  EXPECT_EQ(-4, get_primary_statistic_modifier(12, -4));

  EXPECT_EQ(0, get_primary_statistic_modifier(99, 12));

  EXPECT_EQ(-5, get_primary_statistic_modifier(99, -5));

  EXPECT_EQ(3, get_primary_statistic_modifier(96, 15));

  EXPECT_EQ(-3, get_primary_statistic_modifier(4, -15));

  EXPECT_EQ(0, get_primary_statistic_modifier(1, -3));

  EXPECT_EQ(3, get_primary_statistic_modifier(1, 3));
}
