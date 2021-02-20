#include "gtest/gtest.h"

TEST(SW_Engine_Calculator_DivineCompanionCalculator, calculate_hp)
{
  DivineCompanionCalculator dcc;
  Statistic hp(100);

  Statistic calc_hp = dcc.calculate_hp(hp);

  EXPECT_EQ(130, calc_hp.get_base());
  EXPECT_EQ(130, calc_hp.get_current());
}

TEST(SW_Engine_Calculator_DivineCompanionCalculator, calculate_ap)
{
  DivineCompanionCalculator dcc;
  Statistic ap(50);

  Statistic calc_ap = dcc.calculate_ap(ap);

  EXPECT_EQ(65, calc_ap.get_base());
  EXPECT_EQ(65, calc_ap.get_current());
}

TEST(SW_Engine_Calculator_DivineCompanionCalculator, calculate_damage_modifier)
{
  DivineCompanionCalculator dcc;
  CreaturePtr c = std::make_shared<Creature>();
  c->set_level(40);
  Damage d;
  d.set_modifier(30);

  EXPECT_EQ(50, dcc.calculate_damage_modifier(c, d));
}

