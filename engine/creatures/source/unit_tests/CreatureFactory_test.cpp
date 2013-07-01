#include "gtest/gtest.h"

TEST(SL_Engine_Creatures_CreatureFactory, set_name)
{
  ActionManager am;
  CreaturePtr c = CreatureFactory::create_by_race_and_class(am, "", "", "Rodney", CREATURE_SEX_MALE);

  EXPECT_EQ("Rodney", c->get_name());
}
