#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_WeavingCalculator, calculate_min_points)
{
  WeavingCalculator wc;
  CreaturePtr creature;

  EXPECT_EQ(0, wc.calculate_min_enchant_points(creature));

  creature = std::make_shared<Creature>();

  Skills s;
  s.set_value(SkillType::SKILL_GENERAL_WEAVING, 10);
  creature->set_skills(s);

  EXPECT_EQ(0, wc.calculate_min_enchant_points(creature));

  for (uint i = 20; i <= 100; i += 20)
  {
    s.set_value(SkillType::SKILL_GENERAL_WEAVING, i);
    creature->set_skills(s);

    EXPECT_EQ(i / 20, wc.calculate_min_enchant_points(creature));
  }
}

TEST(SL_Engine_Calculators_WeavingCalculator, calculate_max_points)
{
  WeavingCalculator wc;
  CreaturePtr creature;

  EXPECT_EQ(0, wc.calculate_max_enchant_points(creature));

  creature = std::make_shared<Creature>();

  Skills s;
  s.set_value(SkillType::SKILL_GENERAL_WEAVING, 7);
  creature->set_skills(s);

  EXPECT_EQ(0, wc.calculate_max_enchant_points(creature));

  for (uint i = 10; i <= 100; i += 10)
  {
    s.set_value(SkillType::SKILL_GENERAL_WEAVING, i);
    creature->set_skills(s);

    EXPECT_EQ(i / 10, wc.calculate_max_enchant_points(creature));
  }
}

