#include "gtest/gtest.h"

TEST(SL_World_Dice, serialization_id)
{
  Dice dice;

  EXPECT_EQ(CLASS_ID_DICE, dice.get_class_identifier());
}

