#include "gtest/gtest.h"

TEST(SW_Engine_CowardiceCalculator, get_pct_chance_turn_to_fight)
{
  CreaturePtr creature = std::make_shared<Creature>();
  CowardiceCalculator cc;

  std::map<CreatureSize, int> size_map = { {CreatureSize::CREATURE_SIZE_TINY, 4},
                                           {CreatureSize::CREATURE_SIZE_SMALL, 8},
                                           {CreatureSize::CREATURE_SIZE_MEDIUM, 10},
                                           {CreatureSize::CREATURE_SIZE_LARGE, 15},
                                           {CreatureSize::CREATURE_SIZE_HUGE, 20},
                                           {CreatureSize::CREATURE_SIZE_BEHEMOTH, 25} };

  EXPECT_EQ(10, cc.get_pct_chance_turn_to_fight(nullptr));

  for (const auto s_it : size_map)
  {
    creature->set_size(s_it.first);
    EXPECT_EQ(s_it.second, cc.get_pct_chance_turn_to_fight(creature));
  }
}

TEST(SW_Engine_CowardiceCalculator, get_pct_chance_rage_fight)
{
  CreaturePtr creature = std::make_shared<Creature>();
  CowardiceCalculator cc;

  std::map<CreatureSize, int> size_map = { {CreatureSize::CREATURE_SIZE_TINY, 4},
                                           {CreatureSize::CREATURE_SIZE_SMALL, 8},
                                           {CreatureSize::CREATURE_SIZE_MEDIUM, 10},
                                           {CreatureSize::CREATURE_SIZE_LARGE, 15},
                                           {CreatureSize::CREATURE_SIZE_HUGE, 20},
                                           {CreatureSize::CREATURE_SIZE_BEHEMOTH, 25} };

  EXPECT_EQ(10, cc.get_pct_chance_rage_fight(nullptr));

  for (const auto s_it : size_map)
  {
    creature->set_size(s_it.first);
    EXPECT_EQ(s_it.second, cc.get_pct_chance_rage_fight(creature));
  }
}

