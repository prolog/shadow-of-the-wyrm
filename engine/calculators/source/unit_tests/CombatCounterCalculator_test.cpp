#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_CombatCounterCalculator, pct_chance_counter_strike)
{
  CreaturePtr creature = std::make_shared<Creature>();
  CombatCounterCalculator ccc;
  Statistic hp(50);
  creature->set_hit_points(hp);

  EXPECT_EQ(0, ccc.calc_pct_chance_counter_strike(nullptr));
  EXPECT_EQ(0, ccc.calc_pct_chance_counter_strike(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_COMBAT, 20);
  
  EXPECT_EQ(2, ccc.calc_pct_chance_counter_strike(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_COMBAT, 60);

  EXPECT_EQ(6, ccc.calc_pct_chance_counter_strike(creature));

  creature->get_dexterity_ref().set_base_current(32);

  EXPECT_EQ(12, ccc.calc_pct_chance_counter_strike(creature));

  hp.set_current(-2);
  creature->set_hit_points(hp);

  EXPECT_EQ(0, ccc.calc_pct_chance_counter_strike(creature));
}

