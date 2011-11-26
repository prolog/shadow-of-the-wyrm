#include "gtest/gtest.h"

TEST(SL_Engine_CreatureFactory, set_name)
{
  Creature c = CreatureFactory::create_by_race_and_class("", "", "Rodney");

  EXPECT_EQ("Rodney", c.get_name());
}
