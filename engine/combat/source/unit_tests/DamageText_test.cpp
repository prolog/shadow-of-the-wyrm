#include "gtest/gtest.h"

TEST(SW_Engine_Combat_DamageText, get_colour)
{
  CreaturePtr creature = CreaturePtr(new Creature());
  ControllerPtr null_controller;
  creature->set_is_player(false, null_controller);

  Statistic hp(20);
  creature->set_hit_points(hp);

  DamageText dt;

  EXPECT_EQ(Colour::COLOUR_WHITE, dt.get_colour(creature));

  creature->set_is_player(true, null_controller);

  EXPECT_EQ(Colour::COLOUR_WHITE, dt.get_colour(creature));

  hp.set_current(3);
  creature->set_hit_points(hp);

  EXPECT_EQ(Colour::COLOUR_RED, dt.get_colour(creature));
}
