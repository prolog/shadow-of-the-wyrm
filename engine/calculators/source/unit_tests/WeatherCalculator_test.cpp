#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_WeatherCalculator, pct_chance_shimmer)
{
  WeatherCalculator wc;
  Dimensions dim;
  MapPtr map = std::make_shared<Map>(dim);
  map->set_map_type(MapType::MAP_TYPE_WORLD);
 
  EXPECT_EQ(0, wc.calculate_pct_chance_shimmer(map, 0));
  EXPECT_EQ(0, wc.calculate_pct_chance_shimmer(map, 15));
  EXPECT_EQ(10, wc.calculate_pct_chance_shimmer(map, 20));
  EXPECT_EQ(20, wc.calculate_pct_chance_shimmer(map, 40));
  EXPECT_EQ(40, wc.calculate_pct_chance_shimmer(map, 80));
  EXPECT_EQ(37, wc.calculate_pct_chance_shimmer(map, 75));
  EXPECT_EQ(50, wc.calculate_pct_chance_shimmer(map, 100));
  EXPECT_EQ(100, wc.calculate_pct_chance_shimmer(map, 5000));
}

