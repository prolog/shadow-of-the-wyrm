#include "gtest/gtest.h"
#include "CreatureCalculator.hpp"

TEST(SW_Engine_Creatures_SlownessStatusEffect, confirm_speed_bonus)
{
  CreatureCalculator cc;
  CreaturePtr creature = std::make_shared<Creature>();
  Statistic speed(50);
  creature->set_speed(speed);

  SlownessStatusEffect sse;

  sse.apply_change(creature, 1);

  EXPECT_EQ(75, creature->get_speed().get_current());

  // Simulate a few turns passing
  cc.update_calculated_values(creature);
  cc.update_calculated_values(creature);
  cc.update_calculated_values(creature);

  EXPECT_EQ(75, creature->get_speed().get_current());
}

