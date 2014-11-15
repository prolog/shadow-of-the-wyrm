#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_SkinCalculator, calculate_chance_successful_skin)
{
  SkinCalculator sc;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  EXPECT_EQ(35, sc.calculate_chance_successful_skin(creature));

  skills.set_value(SKILL_GENERAL_SKINNING, 1);
  creature->set_skills(skills);

  EXPECT_EQ(36, sc.calculate_chance_successful_skin(creature));

  skills.set_value(SKILL_GENERAL_SKINNING, 22);
  creature->set_skills(skills);

  EXPECT_EQ(57, sc.calculate_chance_successful_skin(creature));

  skills.set_value(SKILL_GENERAL_SKINNING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(100, sc.calculate_chance_successful_skin(creature));

}
