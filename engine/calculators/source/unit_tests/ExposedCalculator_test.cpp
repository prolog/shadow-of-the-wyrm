#include "gtest/gtest.h"

TEST(SW_World_Calculator_ExposedCalculator, calc_pct_chance_exposed)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_agility(3);
  
  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_PIERCE, 1.0);

  ExposedCalculator ec;

  EXPECT_EQ(15, ec.calculate_pct_chance_effect(creature));

  creature->set_agility(35);

  EXPECT_EQ(10, ec.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_PIERCE, 0.1);

  EXPECT_EQ(1, ec.calculate_pct_chance_effect(creature));
}

