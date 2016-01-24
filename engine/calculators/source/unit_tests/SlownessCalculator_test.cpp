#include "gtest/gtest.h"

TEST(SW_World_Calculator_SlownessCalculator, calc_pct_chance_slowness)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_agility(2);
  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_COLD, 1.0);

  SlownessCalculator sc;

  EXPECT_EQ(34, sc.calculate_pct_chance_effect(creature));

  creature->set_agility(12);

  EXPECT_EQ(30, sc.calculate_pct_chance_effect(creature));

  creature->set_agility(30);

  EXPECT_EQ(24, sc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_COLD, 0.5);

  EXPECT_EQ(12, sc.calculate_pct_chance_effect(creature));
}

