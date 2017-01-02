#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_ItemEnchantmentCalculators, calculate_pct_chance_brand)
{
  ItemEnchantmentCalculator iec;

  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, false, false));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, true, true));
  EXPECT_EQ(15, iec.calculate_pct_chance_brand(1, true, false));
  EXPECT_EQ(30, iec.calculate_pct_chance_brand(2, true, false));
  EXPECT_EQ(100, iec.calculate_pct_chance_brand(50000, true, false));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(-1, true, false));

}
