#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_EvadeCalculator, calculate_evade_bonus)
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
}
