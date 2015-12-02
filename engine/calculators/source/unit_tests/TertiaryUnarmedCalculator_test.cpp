#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_TertiaryUnarmedCalculator, calculate_knock_back_pct_chance)
{
  CreaturePtr creature;
  TertiaryUnarmedCalculator tuc;

  EXPECT_EQ(0, tuc.calculate_knock_back_pct_chance(creature));

  creature = CreaturePtr(new Creature());
  Statistic str(1);
  creature->set_strength(str);

  EXPECT_EQ(0, tuc.calculate_knock_back_pct_chance(creature));

  str.set_base_current(2);
  creature->set_strength(str);

  EXPECT_EQ(1, tuc.calculate_knock_back_pct_chance(creature));

  str.set_base_current(12);
  creature->set_strength(str);

  EXPECT_EQ(6, tuc.calculate_knock_back_pct_chance(creature));

  str.set_base_current(99);
  creature->set_strength(str);

  EXPECT_EQ(49, tuc.calculate_knock_back_pct_chance(creature));
}
