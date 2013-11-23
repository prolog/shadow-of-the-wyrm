#include "gtest/gtest.h"

TEST(SL_World_Calculator_ParalysisCalculator, calc_pct_chance_paralysis)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_health(5);
  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_LIGHTNING, 1.0);

  ParalysisCalculator pc;

  EXPECT_EQ(15, pc.calculate_pct_chance_effect(creature));

  creature->set_health(14);

  EXPECT_EQ(13, pc.calculate_pct_chance_effect(creature));

  creature->set_health(28);

  EXPECT_EQ(11, pc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_LIGHTNING, 0.5);

  EXPECT_EQ(5, pc.calculate_pct_chance_effect(creature));
}

