#include "gtest/gtest.h"

TEST(SL_World_HungerClock, requires_food)
{
  HungerClock hc;

  hc.set_requires_food(true);

  EXPECT_TRUE(hc.get_requires_food());

  hc.set_requires_food(false);

  EXPECT_FALSE(hc.get_requires_food());
}

TEST(SL_World_HungerClock, raw_hunger_level)
{
  HungerClock hc;
  hc.set_hunger(12345);

  EXPECT_EQ(12345, hc.get_hunger());
}

TEST(SL_World_HungerClock, hunger_levels)
{
  HungerClock hc;

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED);
  EXPECT_TRUE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_FULL);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_TRUE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_TRUE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_HUNGRY);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_TRUE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_STARVING);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_TRUE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_DYING);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_TRUE(hc.is_dying());
}

TEST(SL_World_HungerClock, serialization_id)
{
  HungerClock hc;

  EXPECT_EQ(CLASS_ID_HUNGER_CLOCK, hc.get_class_identifier());
}
