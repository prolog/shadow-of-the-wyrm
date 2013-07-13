#include "gtest/gtest.h"

TEST(SL_World_Calculator_MutenessCalculator, calc_pct_chance_muteness)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  creature->set_charisma(3);

  MutenessCalculator pc;

  EXPECT_EQ(30, pc.calculate_pct_chance_effect(creature));

  creature->set_charisma(28);

  EXPECT_EQ(23, pc.calculate_pct_chance_effect(creature));
}

