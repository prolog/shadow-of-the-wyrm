#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_ArcanaPointsCalculator, calculate_arcana_point_bonus)
{
  Creature c;

  c.set_strength(10);
  c.set_dexterity(10);
  c.set_agility(14);
  c.set_health(15);
  c.set_intelligence(12);
  c.set_willpower(14);
  c.set_charisma(16);

  CreaturePtr cp = std::make_shared<Creature>(c);

  EXPECT_EQ(2, ArcanaPointsCalculator::calculate_arcana_points_bonus(cp));

  cp->set_intelligence(20);

  EXPECT_EQ(6, ArcanaPointsCalculator::calculate_arcana_points_bonus(cp));

  cp->set_willpower(22);

  EXPECT_EQ(8, ArcanaPointsCalculator::calculate_arcana_points_bonus(cp));
}
