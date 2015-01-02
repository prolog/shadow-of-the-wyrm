#include "gtest/gtest.h"

TEST(SL_World_Calculator_MutenessCalculator, calc_pct_chance_muteness)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_charisma(3);
  
  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_HOLY, 1.0);

  MutenessCalculator mc;

  EXPECT_EQ(30, mc.calculate_pct_chance_effect(creature));

  creature->set_charisma(28);

  EXPECT_EQ(23, mc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DamageType::DAMAGE_TYPE_HOLY, 0.5);

  EXPECT_EQ(11, mc.calculate_pct_chance_effect(creature));
}

