#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_ScythingCalculator, pct_chance_scything_continues)
{
  ScythingCalculator sc;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_EQ(0, sc.calc_pct_chance_scything_continues(nullptr, SkillType::SKILL_MELEE_LONG_BLADES, 1));
  EXPECT_EQ(0, sc.calc_pct_chance_scything_continues(nullptr, SkillType::SKILL_MELEE_LONG_BLADES, 1));

  creature->get_skills().set_value(SkillType::SKILL_MELEE_LONG_BLADES, 100);

  EXPECT_EQ(90, sc.calc_pct_chance_scything_continues(creature, SkillType::SKILL_MELEE_LONG_BLADES, 1));
  EXPECT_EQ(70, sc.calc_pct_chance_scything_continues(creature, SkillType::SKILL_MELEE_LONG_BLADES, 3));
  EXPECT_EQ(30, sc.calc_pct_chance_scything_continues(creature, SkillType::SKILL_MELEE_LONG_BLADES, 7));
}

