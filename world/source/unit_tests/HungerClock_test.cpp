#include "gtest/gtest.h"

TEST(SW_World_HungerClock, requires_food)
{
  HungerClock hc;

  hc.set_requires_food(true);

  EXPECT_TRUE(hc.get_requires_food());

  hc.set_requires_food(false);

  EXPECT_FALSE(hc.get_requires_food());
}

TEST(SW_World_HungerClock, raw_hunger_level)
{
  HungerClock hc;
  hc.set_hunger(12345);

  EXPECT_EQ(12345, hc.get_hunger());
}

TEST(SW_World_HungerClock, hunger_levels)
{
  HungerClock hc;

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED);
  EXPECT_TRUE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());
  EXPECT_FALSE(hc.is_normal_or_worse());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_FULL);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_TRUE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());
  EXPECT_FALSE(hc.is_normal_or_worse());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_TRUE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());
  EXPECT_TRUE(hc.is_normal_or_worse());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_HUNGRY);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_TRUE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());
  EXPECT_TRUE(hc.is_normal_or_worse());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_STARVING);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_TRUE(hc.is_starving());
  EXPECT_FALSE(hc.is_dying());
  EXPECT_TRUE(hc.is_normal_or_worse());

  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_DYING);
  EXPECT_FALSE(hc.is_stuffed());
  EXPECT_FALSE(hc.is_full());
  EXPECT_FALSE(hc.is_normal());
  EXPECT_FALSE(hc.is_hungry());
  EXPECT_FALSE(hc.is_starving());
  EXPECT_TRUE(hc.is_dying());
  EXPECT_TRUE(hc.is_normal_or_worse());
}

TEST(SW_World_HungerClock, can_eat)
{
  // When stuffed, can only eat an amount that'll be under the huner clock.
  HungerClock hc;
  hc.set_hunger(16000);
  EXPECT_FALSE(hc.can_eat(0));
  EXPECT_FALSE(hc.can_eat(500));

  hc.set_hunger(15400);
  EXPECT_TRUE(hc.can_eat(0));
  EXPECT_TRUE(hc.can_eat(500));
  EXPECT_FALSE(hc.can_eat(700));

  // When not stuffed, can always eat.
  hc.set_hunger(HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL);
  EXPECT_TRUE(hc.can_eat(0));
  EXPECT_TRUE(hc.can_eat(750));
  EXPECT_TRUE(hc.can_eat(10000));

}

TEST(SW_World_HungerClock, serialization_id)
{
  HungerClock hc;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_HUNGER_CLOCK, hc.get_class_identifier());
}

TEST(SW_World_HungerClock, saveload)
{
  HungerClock hc, hc2;

  hc.set_requires_food(true);
  hc.set_hunger(1234);

  ostringstream ss;

  hc.serialize(ss);

  istringstream iss(ss.str());

  hc2.deserialize(iss);

  EXPECT_TRUE(hc == hc2);
}
