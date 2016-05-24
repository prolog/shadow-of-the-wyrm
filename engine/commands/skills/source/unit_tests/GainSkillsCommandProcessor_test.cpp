#include "gtest/gtest.h"

TEST(SL_World_Engine_Commands_Skills_GainSkillsCommandProcessor, can_process)
{
  CreaturePtr cp = std::make_shared<Creature>();
  Skills& skills = cp->get_skills();

  GainSkillsCommandProcessor gscp;

  EXPECT_FALSE(gscp.can_process(nullptr));

  // False because 0 skill pts
  EXPECT_FALSE(gscp.can_process(cp));

  cp->set_skill_points(10);

  // True because now > 0 skill points
  EXPECT_TRUE(gscp.can_process(cp));

  skills.set_all_to(100);

  // False again because skills are maxed
  EXPECT_FALSE(gscp.can_process(cp));
}
