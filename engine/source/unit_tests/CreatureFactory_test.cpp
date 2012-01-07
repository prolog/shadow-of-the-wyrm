#include "gtest/gtest.h"

TEST(SL_Engine_CreatureFactory, set_name)
{
  CreaturePtr c = CreatureFactory::create_by_race_and_class("", "", "Rodney", CREATURE_SEX_MALE);

  EXPECT_EQ("Rodney", c->get_name());
}
