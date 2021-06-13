#include "gtest/gtest.h"

TEST(SW_Engine_Calculator_KilnCalculator, pct_chance_brand)
{
  KilnCalculator kc;
  EXPECT_EQ(0, kc.calc_pct_chance_brand());
}

TEST(SW_Engine_Calculator_KilnCalculator, min_enchants)
{
  KilnCalculator kc;
  CreaturePtr creature = std::make_shared<Creature>();

  for (int i = 5; i < 100; i += 10)
  {
    creature->get_skills().set_value(SkillType::SKILL_GENERAL_CRAFTING, i);

    int exp_val = (i < 10) ? 0 : 1;
    EXPECT_EQ(exp_val, kc.calc_min_free_enchants(creature));
  }
}

TEST(SW_Engine_Calculator_KilnCalculator, max_enchants)
{
  KilnCalculator kc;
  CreaturePtr creature = std::make_shared<Creature>();

  for (int i = 5; i < 100; i += 10)
  {
    creature->get_skills().set_value(SkillType::SKILL_GENERAL_CRAFTING, i);

    int exp_val = i / 10;
    EXPECT_EQ(exp_val, kc.calc_max_free_enchants(creature));
  }
}
