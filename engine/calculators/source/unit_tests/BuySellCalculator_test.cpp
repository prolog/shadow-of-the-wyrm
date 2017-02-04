#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_BuySellCalculator, pct_chance_bargain)
{
  CreaturePtr creature;
  BuySellCalculator bsc;

  EXPECT_EQ(0, bsc.calc_pct_chance_bargain(creature));

  creature = std::make_shared<Creature>();

  EXPECT_EQ(0, bsc.calc_pct_chance_bargain(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_BARGAINING, 12);

  EXPECT_EQ(12, bsc.calc_pct_chance_bargain(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_BARGAINING, 87);

  EXPECT_EQ(87, bsc.calc_pct_chance_bargain(creature));
}

TEST(SW_Engine_Calculators_BuySellCalculator, pct_discount_buy)
{
  BuySellCalculator bsc;
  EXPECT_EQ(0, bsc.calc_pct_discount_buy(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_charisma_ref().set_base_current(20);

  EXPECT_EQ(5, bsc.calc_pct_discount_buy(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_BARGAINING, 50);

  EXPECT_EQ(17, bsc.calc_pct_discount_buy(creature));
}

TEST(SW_Engine_Calculators_BuySellCalculator, pct_premium_sell)
{
  BuySellCalculator bsc;
  EXPECT_EQ(0, bsc.calc_pct_premium_sell(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_charisma_ref().set_base_current(10);

  EXPECT_EQ(2, bsc.calc_pct_premium_sell(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_BARGAINING, 42);

  EXPECT_EQ(13, bsc.calc_pct_premium_sell(creature));
}

