#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_ForestCalculator, pct_chance_fruit)
{
  ForestCalculator fc;

  EXPECT_EQ(10, fc.calculate_pct_chance_fruit(TILE_TYPE_WILD_ORCHARD));
  EXPECT_EQ(0, fc.calculate_pct_chance_fruit(TILE_TYPE_FOREST));
  EXPECT_EQ(0, fc.calculate_pct_chance_fruit(TILE_TYPE_DUNGEON_COMPLEX));
}

TEST(SL_Engine_Calculators_ForestCalculator, pct_chance_evergreen)
{
  ForestCalculator fc;

  int world_height = 100;
  Coordinate c(48, 48);

  EXPECT_EQ(0, fc.calculate_pct_chance_evergreen(world_height, c));

  // Should be 7.5 - becomes 7.
  c.first = 65;
  EXPECT_EQ(7, fc.calculate_pct_chance_evergreen(world_height, c));

  c.first = 80;
  EXPECT_EQ(30, fc.calculate_pct_chance_evergreen(world_height, c));
}
