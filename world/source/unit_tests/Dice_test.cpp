#include "gtest/gtest.h"

TEST(SW_World_Dice, min)
{
  Dice dice1(1,2,0);

  EXPECT_EQ(1, dice1.min());

  dice1.set_modifier(3);

  EXPECT_EQ(4, dice1.min());
}

TEST(SW_World_Dice, avg)
{
  Dice dice1(6,6,0);

  EXPECT_EQ(21, dice1.avg());

  dice1.set_modifier(12);

  EXPECT_EQ(33, dice1.avg());
}

TEST(SW_World_Dice, max)
{
  Dice dice1(3, 4, 0);

  EXPECT_EQ(12, dice1.max());

  Dice dice2(2, 12, 7);

  EXPECT_EQ(31, dice2.max());

  Dice dice3(0, 20, 0);

  EXPECT_EQ(0, dice3.max());
}

TEST(SW_World_Dice, serialization_id)
{
  Dice dice;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DICE, dice.get_class_identifier());
}

TEST(SW_World_Dice, saveload)
{
  Dice d(5, 6, 7);
  Dice d2;

  ostringstream ss;

  d.serialize(ss);

  istringstream iss(ss.str());

  d2.deserialize(iss);

  EXPECT_TRUE(d == d2);
}
