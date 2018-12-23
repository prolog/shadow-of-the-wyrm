#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_PapercraftCalculator, calculate_pct_chance_success)
{
  PapercraftCalculator pc;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_EQ(0, pc.calculate_pct_chance_success(nullptr));
  EXPECT_EQ(50, pc.calculate_pct_chance_success(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_PAPERCRAFT, 30);

  EXPECT_EQ(65, pc.calclate_pct_chance_success(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_PAPERCRAFT, 100);

  EXPECT_EQ(100, pc.calclate_pct_chance_success(creature));
}