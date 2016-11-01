#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_ScribingCalculator, calc_castings_per_scroll)
{
  ScribingCalculator sc;
  CreaturePtr creature;

  EXPECT_EQ(7, sc.calc_castings_per_scroll(creature));

  creature = std::make_shared<Creature>();

  EXPECT_EQ(7, sc.calc_castings_per_scroll(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_SCRIBING, 15);

  EXPECT_EQ(7, sc.calc_castings_per_scroll(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_SCRIBING, 25);

  EXPECT_EQ(6, sc.calc_castings_per_scroll(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_SCRIBING, 60);

  EXPECT_EQ(4, sc.calc_castings_per_scroll(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_SCRIBING, 100);

  EXPECT_EQ(2, sc.calc_castings_per_scroll(creature));
}
