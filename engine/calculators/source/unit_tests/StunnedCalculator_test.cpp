#include "gtest/gtest.h"

TEST(SL_World_Calculator_StunnedCalculator, calc_pct_chance_stunned)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_dexterity(3);
  
  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_POUND, 1.0);

  StunnedCalculator sc;

  EXPECT_EQ(15, sc.calculate_pct_chance_effect(creature));

  creature->set_dexterity(35);

  EXPECT_EQ(10, sc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_POUND, 0.5);

  EXPECT_EQ(5, sc.calculate_pct_chance_effect(creature));
}

