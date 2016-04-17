#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_SmithingCalculator, pct_chances_extra_point)
{
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  skills.set_value(SkillType::SKILL_GENERAL_SMITHING, 56);
  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 42);
  skills.set_value(SkillType::SKILL_GENERAL_JEWELER, 33);

  creature->set_skills(skills);

  vector<int> expected_chances_sm = {56, 14};
  vector<int> expected_chances_jw = {33, 14};

  SmithingCalculator sc;

  EXPECT_EQ(expected_chances_sm, sc.calculate_pct_chances_extra_point(creature, SkillType::SKILL_GENERAL_SMITHING));
  EXPECT_EQ(expected_chances_jw, sc.calculate_pct_chances_extra_point(creature, SkillType::SKILL_GENERAL_JEWELER));
}
