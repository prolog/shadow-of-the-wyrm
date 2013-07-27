#include "gtest/gtest.h"

// For every 5 points of Str > 10, +1 dam.
TEST(SL_World_Calculators_PhysicalDamageCalculator, get_statistic_based_damage_modifier)
{
  PhysicalDamageCalculator pdc(ATTACK_TYPE_MELEE_PRIMARY);

  CreaturePtr creature = boost::make_shared<Creature>();
  creature->set_strength(3);

  EXPECT_EQ(0, pdc.get_statistic_based_damage_modifier(creature));

  creature->set_strength(16);

  EXPECT_EQ(1, pdc.get_statistic_based_damage_modifier(creature));

  creature->set_strength(47);

  EXPECT_EQ(7, pdc.get_statistic_based_damage_modifier(creature));
}
