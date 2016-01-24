#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_HitPointsCalculator, calculate_hit_points_bonus)
{
  Creature c;

  c.set_strength(10);
  c.set_dexterity(12);
  c.set_agility(14);
  c.set_health(8);
  c.set_intelligence(14);
  c.set_willpower(19);
  c.set_charisma(12);

  CreaturePtr cp = std::make_shared<Creature>(c);

  EXPECT_EQ(0, HitPointsCalculator::calculate_hit_points_bonus(cp));

  cp->set_health(11);

  EXPECT_EQ(1, HitPointsCalculator::calculate_hit_points_bonus(cp));

  cp->set_health(26);

  EXPECT_EQ(16, HitPointsCalculator::calculate_hit_points_bonus(cp));
}
