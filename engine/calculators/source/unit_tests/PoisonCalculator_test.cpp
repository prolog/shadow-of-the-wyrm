#include "gtest/gtest.h"

TEST(SL_World_Calculator_PoisonCalculator, calc_pct_chance_poison)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  creature->set_health(10);
  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_POISON, 1.0);

  PoisonCalculator pc;

  EXPECT_EQ(23, pc.calculate_pct_chance_effect(creature));

  creature->set_health(28);

  EXPECT_EQ(20, pc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_POISON, 0.25);

  EXPECT_EQ(5, pc.calculate_pct_chance_effect(creature));
}

TEST(SL_World_Calculator_PoisonCalculator, calc_damage_per_tick)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  creature->set_health(4);

  PoisonCalculator pc;

  EXPECT_EQ(2, pc.calculate_damage_per_tick(creature));

  creature->set_health(9);
  
  EXPECT_EQ(1, pc.calculate_damage_per_tick(creature));
}

