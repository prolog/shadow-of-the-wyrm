#include "gtest/gtest.h"

TEST(SL_World_Calculator_ParalysisCalculator, calc_pct_chance_paralysis)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  creature->set_health(5);

  ParalysisCalculator pc;

  EXPECT_EQ(15, pc.calculate_pct_chance_effect(creature));

  creature->set_health(14);

  EXPECT_EQ(13, pc.calculate_pct_chance_effect(creature));

  creature->set_health(28);

  EXPECT_EQ(11, pc.calculate_pct_chance_effect(creature));
}

