#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_ItemDropRateCalculator, calculate_pct_chance_item_drop)
{
  CreaturePtr creature;
  ItemDropRateCalculator idrc;

  EXPECT_EQ(15, idrc.calculate_pct_chance_currency_drop(creature));

  creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 42);

  EXPECT_EQ(21, idrc.calculate_pct_chance_currency_drop(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 90);

  EXPECT_EQ(28, idrc.calculate_pct_chance_currency_drop(creature));
}

TEST(SW_Engine_Calculators_ItemDropRateCalculator, calculate_pct_chance_currency_drop)
{
  CreaturePtr creature;
  ItemDropRateCalculator idrc;

  EXPECT_EQ(5, idrc.calculate_pct_chance_item_drop(creature));

  creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 37);

  EXPECT_EQ(6, idrc.calculate_pct_chance_item_drop(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 99);

  EXPECT_EQ(9, idrc.calculate_pct_chance_item_drop(creature));
}
