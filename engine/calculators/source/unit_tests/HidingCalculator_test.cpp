#include "gtest/gtest.h"
#include "MobileDecisionStrategy.hpp"

TEST(SW_Engine_Calculators_HidingCalculator, calculate_pct_chance_hide)
{
  HidingCalculator hc;
  CreaturePtr creature;
  MapPtr map;

  EXPECT_EQ(0, hc.calculate_pct_chance_hide(creature, map, TimeOfDayType::TIME_OF_DAY_UNDEFINED).first);

  Dimensions dim;
  map = std::make_shared<Map>(dim);

  creature = std::make_shared<Creature>();
  creature->set_id("cr1");

  EXPECT_EQ(100, hc.calculate_pct_chance_hide(creature, map, TimeOfDayType::TIME_OF_DAY_UNDEFINED).first);
}

TEST(SW_Engine_Calculators_HidingCalculator, calculate_pct_chance_hidden_after_attacking)
{
  HidingCalculator hc;
  CreaturePtr creature = std::make_shared<Creature>();

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_HIDING, 2);
  EXPECT_EQ(1, hc.calculate_pct_chance_hidden_after_attacking(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_HIDING, 10);
  EXPECT_EQ(5, hc.calculate_pct_chance_hidden_after_attacking(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_HIDING, 25);
  EXPECT_EQ(12, hc.calculate_pct_chance_hidden_after_attacking(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_HIDING, 50);
  EXPECT_EQ(25, hc.calculate_pct_chance_hidden_after_attacking(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_HIDING, 75);
  EXPECT_EQ(37, hc.calculate_pct_chance_hidden_after_attacking(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_HIDING, 100);
  EXPECT_EQ(50, hc.calculate_pct_chance_hidden_after_attacking(creature));
}