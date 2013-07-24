#include "gtest/gtest.h"

TEST(SL_World_Calculator_StoneCalculator, calc_pct_chance_stone)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  creature->set_health(3);
  
  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_SHADOW, 1.0);

  StoneCalculator sc;

  EXPECT_EQ(5, sc.calculate_pct_chance_effect(creature));

  creature->set_health(40);

  EXPECT_EQ(3, sc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_SHADOW, 0.25);

  EXPECT_EQ(0, sc.calculate_pct_chance_effect(creature));
}

