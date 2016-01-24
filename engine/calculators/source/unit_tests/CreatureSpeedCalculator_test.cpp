#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_Calculators_CreatureSpeedCalculator, calculate_creature_speed_base)
{
  Statistic speed(47);
  CreaturePtr c = std::make_shared<Creature>();
  c->set_speed(speed);

  CreatureSpeedCalculator csc;

  EXPECT_EQ(0, csc.calculate(nullptr));

  EXPECT_EQ(47, csc.calculate(c));
}

TEST(SW_Engine_Calculators_CreatureSpeedCalculator, calculate_burdened_and_strained)
{
  Statistic speed(50);
  Statistic str(10);
  CreaturePtr c = std::make_shared<Creature>();
  c->set_speed(speed);
  c->set_strength(str);

  // Add some items to increase weight.
  ItemPtr amulet = std::make_shared<Amulet>();
  Weight weight(16);
  amulet->set_quantity(110);
  amulet->set_weight(weight);

  c->get_inventory()->add_front(amulet);

  CreatureSpeedCalculator csc;
  
  int exp_speed = static_cast<int>(50 * 1.2);
  EXPECT_EQ(exp_speed, csc.calculate(c));

  amulet->set_quantity(200);

  exp_speed = static_cast<int>(50 * 1.5);
  EXPECT_EQ(exp_speed, csc.calculate(c));
}