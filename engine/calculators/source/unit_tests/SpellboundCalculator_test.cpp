#include "gtest/gtest.h"

TEST(SL_World_Calculator_SpellboundCalculator, calc_pct_chance_spellbound)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_willpower(3);
  
  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_ARCANE, 1.0);

  SpellboundCalculator sc;

  EXPECT_EQ(10, sc.calculate_pct_chance_effect(creature));

  creature->set_willpower(51);

  EXPECT_EQ(5, sc.calculate_pct_chance_effect(creature));

  creature->get_resistances().set_resistance_value(DAMAGE_TYPE_ARCANE, 0.8);

  EXPECT_EQ(4, sc.calculate_pct_chance_effect(creature));
}

