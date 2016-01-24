#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_SoakCalculator, calculate_soak)
{
  Creature c;
  c.set_strength(15);
  c.set_dexterity(13);
  c.set_agility(16);
  c.set_health(10);
  c.set_intelligence(12);
  c.set_willpower(9);
  c.set_charisma(8);

  CreaturePtr cp(new Creature(c));

  EXPECT_EQ(0, SoakCalculator::calculate_soak(cp));

  cp->set_health(15);

  EXPECT_EQ(1, SoakCalculator::calculate_soak(cp));

  cp->set_health(30);

  EXPECT_EQ(5, SoakCalculator::calculate_soak(cp));
}
