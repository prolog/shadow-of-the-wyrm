#include "gtest/gtest.h"

TEST(SL_Engine_Creatures_CreatureFactory, set_name)
{
  ActionManager am;

  CreatureFactory cf;
  CreaturePtr c = cf.create_by_race_and_class(am, "", "", "Rodney", CreatureSex::CREATURE_SEX_MALE);

  EXPECT_EQ("Rodney", c->get_name());
}
