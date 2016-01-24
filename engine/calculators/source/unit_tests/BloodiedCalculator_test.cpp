#include "gtest/gtest.h"

TEST(SW_World_Calculator_BloodiedCalculator, calc_pct_chance_bloodied)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_strength(3);
  
  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_SLASH, 1.0);

  BloodiedCalculator bc;

  EXPECT_EQ(15, bc.calculate_pct_chance_effect(creature));

  creature->set_strength(35);

  EXPECT_EQ(10, bc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_SLASH, 0.6);

  EXPECT_EQ(6, bc.calculate_pct_chance_effect(creature));
}

