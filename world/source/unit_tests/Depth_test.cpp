#include "gtest/gtest.h"

TEST(SW_World_Depth, lower)
{
  Depth d(5, 0, 20, 1);
  Depth lower = d.lower();

  EXPECT_EQ(6, lower.get_current());
  EXPECT_EQ(20, lower.get_maximum());

  lower = lower.lower();

  EXPECT_EQ(7, lower.get_current());
  EXPECT_EQ(20, lower.get_maximum());

  Depth lowest(10, 0, 10, 1);
  Depth d2 = lowest.lower();

  EXPECT_TRUE(lowest == d2);
}

TEST(SW_World_Depth, higher)
{
  Depth d(5, -3, 5, 1);
  Depth higher = d.higher();

  EXPECT_EQ(4, higher.get_current());
  EXPECT_EQ(5, higher.get_maximum());

  higher = higher.higher();

  EXPECT_EQ(3, higher.get_current());
  EXPECT_EQ(5, higher.get_maximum());

  for (int i = 0; i < 10; i++)
  {
    higher = higher.higher();
  }

  EXPECT_EQ(-3, higher.get_current());
  EXPECT_EQ(-3, higher.get_minimum());
}

TEST(SW_World_Depth, increment)
{
  Depth depth(0, -10, 10, 2);
  depth = depth.lower();

  EXPECT_EQ(2, depth.get_current());

  depth = depth.higher();
  depth = depth.higher();

  EXPECT_EQ(-2, depth.get_current());
}

TEST(SW_World_Depth, serialization_id)
{
  Depth depth;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DEPTH, depth.get_class_identifier());
}

TEST(SW_World_Depth, saveload)
{
  Depth depth, depth2;

  depth.set_current(5);
  depth.set_maximum(56);

  ostringstream ss;

  depth.serialize(ss);

  istringstream iss(ss.str());

  depth2.deserialize(iss);

  EXPECT_TRUE(depth == depth2);
}