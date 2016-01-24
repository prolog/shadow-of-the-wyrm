#include "gtest/gtest.h"

TEST(SW_World_Dice, max_dice_rolls)
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
