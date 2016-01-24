#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_HungerDamageCalculator, damage_per_tick)
{
  HungerDamageCalculator hdc;
  CreaturePtr null_creature;

  EXPECT_EQ(0, hdc.calculate_hunger_damage(null_creature, 0));
  EXPECT_EQ(10, hdc.calculate_hunger_damage(null_creature, 1));
  EXPECT_EQ(50, hdc.calculate_hunger_damage(null_creature, 5));
  EXPECT_EQ(500, hdc.calculate_hunger_damage(null_creature, 50));
  EXPECT_EQ(1000, hdc.calculate_hunger_damage(null_creature, 100));
}

