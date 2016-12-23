#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_MineCalculator, calculate_pct_chance_magici_shard)
{
  MineCalculator mc;

  EXPECT_EQ(50, mc.calculate_pct_chance_magici_shards(-10));
  EXPECT_EQ(50, mc.calculate_pct_chance_magici_shards(0));
  EXPECT_EQ(55, mc.calculate_pct_chance_magici_shards(5));
  EXPECT_EQ(76, mc.calculate_pct_chance_magici_shards(26));
  EXPECT_EQ(100, mc.calculate_pct_chance_magici_shards(50));
  EXPECT_EQ(100, mc.calculate_pct_chance_magici_shards(1000));
}

