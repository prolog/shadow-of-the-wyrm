#include "gtest/gtest.h"

TEST(SW_Engine_CowardiceCalculator, get_pct_chance_turn_to_fight)
{
  CreaturePtr creature = std::make_shared<Creature>();
  CowardiceCalculator cc;
  EXPECT_EQ(10, cc.get_pct_chance_turn_to_fight(nullptr));
  EXPECT_EQ(10, cc.get_pct_chance_turn_to_fight(creature));
}

TEST(SW_Engine_CowardiceCalculator, get_pct_chance_rage_fight)
{
  CreaturePtr creature = std::make_shared<Creature>();
  CowardiceCalculator cc;
  EXPECT_EQ(10, cc.get_pct_chance_rage_fight(nullptr));
  EXPECT_EQ(10, cc.get_pct_chance_rage_fight(creature));
}

