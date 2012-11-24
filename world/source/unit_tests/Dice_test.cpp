#include "gtest/gtest.h"

TEST(SL_World_Dice, serialization_id)
{
  Dice dice;

  EXPECT_EQ(CLASS_ID_DICE, dice.get_class_identifier());
}

TEST(SL_World_Dice, saveload)
{
  Dice d(5, 6, 7);
  Dice d2;

  ostringstream ss;

  d.serialize(ss);

  istringstream iss(ss.str());

  d2.deserialize(iss);

  EXPECT_TRUE(d == d2);
}
