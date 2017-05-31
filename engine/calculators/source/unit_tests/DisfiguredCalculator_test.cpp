#include "gtest/gtest.h"

TEST(SW_World_Calculator_DisfiguredCalculator, calc_pct_chance_disfigured)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_health(3);
  
  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_ACID, 1.0);

  DisfiguredCalculator dc;

  EXPECT_EQ(15, dc.calculate_pct_chance_effect(creature));

  creature->set_health(35);

  EXPECT_EQ(10, dc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_ACID, 0.3);

  EXPECT_EQ(3, dc.calculate_pct_chance_effect(creature));
}

TEST(SW_World_Calculator_DisfiguredCalculator, calculate_reduction_pcts)
{
  DisfiguredCalculator dc;

  pair<int, int> r_pcts = dc.calculate_reduction_pcts(0);

  EXPECT_EQ(20, r_pcts.first);
  EXPECT_EQ(40, r_pcts.second);

  r_pcts = dc.calculate_reduction_pcts(26);

  EXPECT_EQ(33, r_pcts.first);
  EXPECT_EQ(66, r_pcts.second);

  r_pcts = dc.calculate_reduction_pcts(50);

  EXPECT_EQ(45, r_pcts.first);
  EXPECT_EQ(90, r_pcts.second);

  r_pcts = dc.calculate_reduction_pcts(1000);

  EXPECT_EQ(45, r_pcts.first);
  EXPECT_EQ(90, r_pcts.second);
}