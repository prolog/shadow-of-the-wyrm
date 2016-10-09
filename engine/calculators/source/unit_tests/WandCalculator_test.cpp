#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_WandCalculator, damage_bonus)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 33);
  Statistic willpower(18);
  creature->set_willpower(willpower);
  WandCalculator wc;

  EXPECT_EQ(7, wc.calc_damage_bonus(creature));

  Statistic will2(30);
  creature->set_willpower(will2);

  EXPECT_EQ(8, wc.calc_damage_bonus(creature));
}

TEST(SW_Engine_Calculators_WandCalculator, chance_free_charge)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 33);
  WandCalculator wc;

  EXPECT_EQ(3, wc.calc_pct_chance_free_charge(creature));
}