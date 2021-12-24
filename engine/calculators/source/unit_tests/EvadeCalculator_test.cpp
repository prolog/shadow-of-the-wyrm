#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_EvadeCalculator, calculate_evade_bonus)
{
  Creature c;
  
  c.set_strength(10);
  c.set_dexterity(10);
  c.set_agility(20);
  c.set_health(10);
  c.set_intelligence(15);
  c.set_willpower(15);
  c.set_charisma(10);
  
  CreaturePtr cp = std::make_shared<Creature>(c);
  
  // Agility > 10
  EXPECT_EQ(5, EvadeCalculator::calculate_evade(cp));
  
  // Agility < 10
  cp->set_agility(5);
  EXPECT_EQ(-2, EvadeCalculator::calculate_evade(cp));

  cp->set_level(5);

  EXPECT_EQ(-2, EvadeCalculator::calculate_evade(cp));

  Status s;
  s.set_danger_level(5);
  s.set_value(true);

  cp->set_status(StatusIdentifiers::STATUS_ID_RAGE, s);

  EXPECT_EQ(-7, EvadeCalculator::calculate_evade(cp));

  cp->get_skills().set_value(SkillType::SKILL_GENERAL_ESCAPE, 18);

  EXPECT_EQ(-4, EvadeCalculator::calculate_evade(cp));
}
