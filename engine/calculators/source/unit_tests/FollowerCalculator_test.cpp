#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_FollowerCalculator, calculate_x_in_y_chance_adventurer)
{
  FollowerCalculator fc;
  Depth d;
  d.set_current(1);

  pair<int, int> odds = fc.calculate_x_in_y_chance_adventurer(d);

  EXPECT_EQ(1, odds.first);
  EXPECT_EQ(20, odds.second);

  vector<pair<int, int>> val_and_expect = { {0, 20}, {-3, 20}, {2, static_cast<int>(pow(20, 2))}, {5, static_cast<int>(pow(20, 5))}, {20, static_cast<int>(pow(20, 10))}, {50, static_cast<int>(pow(20, 50))} };

  for (const auto& ve_pair : val_and_expect)
  {
    d.set_current(ve_pair.first);
    odds = fc.calculate_x_in_y_chance_adventurer(d);

    EXPECT_EQ(1, odds.first);
    EXPECT_EQ(ve_pair.second, odds.second);
  }
}

TEST(SW_Engine_Calculators_FollowerCalculator, calculate_x_in_y_chance_hireling)
{
  FollowerCalculator fc;
  Depth d;
  d.set_current(1);

  pair<int, int> odds = fc.calculate_x_in_y_chance_hireling(d);

  EXPECT_EQ(1, odds.first);
  EXPECT_EQ(10, odds.second);

  vector<pair<int, int>> val_and_expect = { {0, 0}, {-3, 0}, {2, 20}, {5, 50}, {10, 100}, {50, 500} };

  for (const auto& ve_pair : val_and_expect)
  {
    d.set_current(ve_pair.first);
    odds = fc.calculate_x_in_y_chance_hireling(d);

    EXPECT_EQ(1, odds.first);
    EXPECT_EQ(ve_pair.second, odds.second);
  }
}

