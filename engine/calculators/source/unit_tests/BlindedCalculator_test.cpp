#include "gtest/gtest.h"

TEST(SW_World_Calculator_BlindedCalculator, calc_pct_chance_blinded)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_health(3);
  
  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_HEAT, 1.0);

  BlindedCalculator bc;

  EXPECT_EQ(15, bc.calculate_pct_chance_effect(creature));

  creature->set_health(35);

  EXPECT_EQ(10, bc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_HEAT, 0.5);

  EXPECT_EQ(5, bc.calculate_pct_chance_effect(creature));
}

