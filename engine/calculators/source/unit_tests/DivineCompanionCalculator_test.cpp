#include "gtest/gtest.h"

TEST(SW_Engine_Calculator_DivineCompanionCalculator, calculate_hp)
{
  CreaturePtr leader = std::make_shared<Creature>();
  leader->get_skills().set_value(SkillType::SKILL_GENERAL_RELIGION, 0);
  DivineCompanionCalculator dcc(leader);
  Statistic hp(100);

  Statistic calc_hp = dcc.calculate_hp(hp);

  EXPECT_EQ(130, calc_hp.get_base());
  EXPECT_EQ(130, calc_hp.get_current());

  leader->get_skills().set_value(SkillType::SKILL_GENERAL_RELIGION, 50);
  calc_hp = dcc.calculate_hp(hp);

  EXPECT_EQ(180, calc_hp.get_base());
  EXPECT_EQ(180, calc_hp.get_current());
}

TEST(SW_Engine_Calculator_DivineCompanionCalculator, calculate_ap)
{
  CreaturePtr leader = std::make_shared<Creature>();
  leader->get_skills().set_value(SkillType::SKILL_GENERAL_RELIGION, 0);
  DivineCompanionCalculator dcc(leader);
  Statistic ap(50);

  Statistic calc_ap = dcc.calculate_ap(ap);

  EXPECT_EQ(65, calc_ap.get_base());
  EXPECT_EQ(65, calc_ap.get_current());

  leader->get_skills().set_value(SkillType::SKILL_GENERAL_RELIGION, 35);
  calc_ap = dcc.calculate_ap(ap);

  EXPECT_EQ(100, calc_ap.get_base());
  EXPECT_EQ(100, calc_ap.get_current());
}

TEST(SW_Engine_Calculator_DivineCompanionCalculator, calculate_damage_modifier)
{
  CreaturePtr leader = std::make_shared<Creature>();
  DivineCompanionCalculator dcc(leader);
  CreaturePtr c = std::make_shared<Creature>();
  c->set_level(40);
  Damage d;
  d.set_modifier(30);

  EXPECT_EQ(50, dcc.calculate_damage_modifier(c, d));

  leader->get_skills().set_value(SkillType::SKILL_GENERAL_RELIGION, 60);

  EXPECT_EQ(110, dcc.calculate_damage_modifier(c, d));
}

