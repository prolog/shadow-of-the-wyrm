#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_DefaultStatusEffectCalculator, pct_chance_effect)
{
  DefaultStatusEffectCalculator dsec;
  
  EXPECT_EQ(0, dsec.calculate_duration_in_minutes(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MEDICINE, 50);

  EXPECT_EQ(0, dsec.calculate_duration_in_minutes(creature));
}

TEST(SW_Engine_Calculators_DefaultStatusEffectCalculator, duration_effect)
{
  DefaultStatusEffectCalculator dsec;
  
  EXPECT_EQ(0, dsec.calculate_duration_in_minutes(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MEDICINE, 50);

  EXPECT_EQ(0, dsec.calculate_duration_in_minutes(creature));
}

TEST(SW_Engine_Calculators_DefaultStatusEffectCalculator, pct_chance_counteract_negative)
{
  DefaultStatusEffectCalculator dsec;

  EXPECT_EQ(0, dsec.pct_chance_counteract_negative(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_EQ(0, dsec.pct_chance_counteract_negative(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MEDICINE, 10);

  EXPECT_EQ(5, dsec.pct_chance_counteract_negative(creature));
  
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MEDICINE, 42);
  
  EXPECT_EQ(37, dsec.pct_chance_counteract_negative(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MEDICINE, 100);

  EXPECT_EQ(95, dsec.pct_chance_counteract_negative(creature));
}

