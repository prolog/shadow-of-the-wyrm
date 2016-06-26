#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_ForagablesCalculator, calculate_pct_chance_foragables)
{
  ForagablesCalculator fc;
  CreaturePtr creature;

  EXPECT_EQ(0, fc.calculate_pct_chance_foragables(creature));

  creature = std::make_shared<Creature>();
  Skills skills;
  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 33);
  creature->set_skills(skills);

  EXPECT_EQ(33, fc.calculate_pct_chance_foragables(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(100, fc.calculate_pct_chance_foragables(creature));
}

TEST(SW_Engine_Calculators_ForagablesCalculator, calculate_pct_chance_herbs)
{
  ForagablesCalculator fc;
  CreaturePtr creature;

  EXPECT_EQ(0, fc.calculate_pct_chance_herbs(creature));

  creature = std::make_shared<Creature>();
  Skills skills;
  skills.set_value(SkillType::SKILL_GENERAL_HERBALISM, 33);
  creature->set_skills(skills);

  EXPECT_EQ(11, fc.calculate_pct_chance_herbs(creature));

  skills.set_value(SkillType::SKILL_GENERAL_HERBALISM, 100);
  creature->set_skills(skills);

  EXPECT_EQ(33, fc.calculate_pct_chance_herbs(creature));
}
