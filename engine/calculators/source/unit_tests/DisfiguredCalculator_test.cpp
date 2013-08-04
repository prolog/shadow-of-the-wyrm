#include "gtest/gtest.h"

TEST(SL_World_Calculator_DisfiguredCalculator, calc_pct_chance_disfigured)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  creature->set_health(3);
  
  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_ACID, 1.0);

  DisfiguredCalculator dc;

  EXPECT_EQ(15, dc.calculate_pct_chance_effect(creature));

  creature->set_health(35);

  EXPECT_EQ(10, dc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_ACID, 0.3);

  EXPECT_EQ(3, dc.calculate_pct_chance_effect(creature));
}

