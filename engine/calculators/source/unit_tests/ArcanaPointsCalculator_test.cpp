#include "gtest/gtest.h"
#include <boost/make_shared.hpp>

using boost::make_shared;

TEST(SL_Engine_Calculators_ArcanaPointsCalculator, calculate_arcana_point_bonus)
{
  Creature c;

  c.set_strength(10);
  c.set_dexterity(10);
  c.set_agility(14);
  c.set_health(15);
  c.set_intelligence(12);
  c.set_willpower(14);
  c.set_charisma(16);
  c.set_valour(55);
  c.set_spirit(60);

  CreaturePtr cp = make_shared<Creature>(c);

  EXPECT_EQ(7, ArcanaPointsCalculator::calculate_arcana_points_bonus(cp));

  cp->set_intelligence(20);

  EXPECT_EQ(11, ArcanaPointsCalculator::calculate_arcana_points_bonus(cp));

  cp->set_willpower(22);

  EXPECT_EQ(13, ArcanaPointsCalculator::calculate_arcana_points_bonus(cp));
}
