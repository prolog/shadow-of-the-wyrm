#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_FenceCalculator, pct_chance_break)
{
  CreaturePtr c = std::make_shared<Creature>();
  c->set_strength(1);

  FenceCalculator fc;

  EXPECT_EQ(0, fc.calc_pct_chance_break(nullptr));
  EXPECT_EQ(2, fc.calc_pct_chance_break(c));

  c->set_strength(30);

  EXPECT_EQ(60, fc.calc_pct_chance_break(c));
}

TEST(SW_Engine_Calculators_FenceCalculator, pct_chance_board)
{
  CreaturePtr c = std::make_shared<Creature>();
  FenceCalculator fc;

  EXPECT_EQ(0, fc.calc_pct_chance_board(nullptr));
  EXPECT_EQ(25, fc.calc_pct_chance_board(c));

  c->set_strength(30);

  EXPECT_EQ(25, fc.calc_pct_chance_board(c));
}
