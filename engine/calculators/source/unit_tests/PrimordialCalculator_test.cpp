#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_PrimordialCalculator, max_skill_castings)
{
  PrimordialCalculator pc;

  EXPECT_EQ(0, pc.get_max_skill_castings(nullptr));

  CreaturePtr c = std::make_shared<Creature>();

  EXPECT_EQ(0, pc.get_max_skill_castings(c));

  c->get_skills().set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, 1);

  EXPECT_EQ(1, pc.get_max_skill_castings(c));

  c->get_skills().set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, 12);

  EXPECT_EQ(1, pc.get_max_skill_castings(c));
  
  c->get_skills().set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, 43);

  EXPECT_EQ(4, pc.get_max_skill_castings(c));
  
  c->get_skills().set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, 100);

  EXPECT_EQ(10, pc.get_max_skill_castings(c));
}

