#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_HungerCalculator, damage_per_tick)
{
  HungerCalculator hc;
  CreaturePtr null_creature;

  EXPECT_EQ(0, hc.calculate_hunger_damage(null_creature, 0));
  EXPECT_EQ(10, hc.calculate_hunger_damage(null_creature, 1));
  EXPECT_EQ(50, hc.calculate_hunger_damage(null_creature, 5));
  EXPECT_EQ(500, hc.calculate_hunger_damage(null_creature, 50));
  EXPECT_EQ(1000, hc.calculate_hunger_damage(null_creature, 100));
}

TEST(SW_Engine_Calculators_HungerCalculator, chance_to_mark_health)
{
  HungerCalculator hc;

  EXPECT_EQ(20, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_NORMAL, true));
  EXPECT_EQ(100, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_NORMAL, false));

  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_DYING, true));
  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_DYING, false));

  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_FULL, true));
  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_FULL, false));

  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_HUNGRY, true));
  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_HUNGRY, false));

  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_STARVING, true));
  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_STARVING, false));

  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_STUFFED, true));
  EXPECT_EQ(0, hc.calculate_pct_chance_mark_health(HungerLevel::HUNGER_LEVEL_STUFFED, false));

}

TEST(SW_Engine_Calculators_HungerCalculator, pct_chance_hunger_while_sated)
{
  HungerCalculator hc;
  EXPECT_EQ(15, hc.calculate_pct_chance_hunger_while_sated());
}

