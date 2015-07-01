#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_CreatureSpeedCalculator, calculate_creature_speed)
{
  Statistic speed(47);
  CreaturePtr c = std::make_shared<Creature>();
  c->set_speed(speed);

  CreatureSpeedCalculator csc;

  EXPECT_EQ(0, csc.calculate(nullptr));

  EXPECT_EQ(47, csc.calculate(c));
}

