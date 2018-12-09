#include "gtest/gtest.h"

// This needs a unit test because Lua scripts will depend on this value
// not changing.
TEST(SW_World_Depth, depth_inf_constant)
{
  EXPECT_TRUE(Depth::DEPTH_INFINITE == "inf");
}

TEST(SW_World_Depth, lower)
{
  Depth d(5, 0, 20, 1, true);
  Depth lower = d.lower();

  EXPECT_EQ(6, lower.get_current());
  EXPECT_EQ(20, lower.get_maximum());

  lower = lower.lower();

  EXPECT_EQ(7, lower.get_current());
  EXPECT_EQ(20, lower.get_maximum());

  Depth lowest(10, 0, 10, 1, true);
  Depth d2 = lowest.lower();

  EXPECT_TRUE(lowest == d2);
}

TEST(SW_World_Depth, lower_no_limit)
{
  Depth d(5, 0, 20, 1, true);
  d.set_has_maximum(false);

  for (int i = 1; i < 30; i++)
  {
    d = d.lower();
  }

  EXPECT_TRUE(d.has_more_levels(Direction::DIRECTION_DOWN));
}

TEST(SW_World_Depth, higher)
{
  Depth d(5, -3, 5, 1, true);
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

TEST(SW_World_Depth, higher_no_limit)
{
  Depth d(1, -20, 20, 1, true);
  d.set_has_maximum(false);

  for (int i = 1; i < 30; i++)
  {
    d = d.higher();
  }

  EXPECT_TRUE(d.has_more_levels(Direction::DIRECTION_UP));
}

TEST(SW_World_Depth, increment)
{
  Depth depth(0, -10, 10, 2, true);
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
  depth.set_has_maximum(false);

  ostringstream ss;

  depth.serialize(ss);

  istringstream iss(ss.str());

  depth2.deserialize(iss);

  EXPECT_TRUE(depth == depth2);
  EXPECT_FALSE(depth2.has_maximum());
}

TEST(SW_World_Depth, has_more_levels_invalid_directions)
{
  Depth depth(0, -10, 10, 1, true);
  vector<Direction> invalid_dirs = {Direction::DIRECTION_NORTH_EAST,
                                    Direction::DIRECTION_NORTH,
                                    Direction::DIRECTION_NORTH_WEST,
                                    Direction::DIRECTION_EAST,
                                    Direction::DIRECTION_NULL,
                                    Direction::DIRECTION_WEST,
                                    Direction::DIRECTION_SOUTH_EAST,
                                    Direction::DIRECTION_SOUTH,
                                    Direction::DIRECTION_SOUTH_WEST};

  for (const Direction id : invalid_dirs)
  {
    EXPECT_FALSE(depth.has_more_levels(id));
  }
}

TEST(SW_World_Depth, has_more_levels_desc)
{
  Depth depth(0, 0, 2, 1, true);

  EXPECT_TRUE(depth.has_more_levels(Direction::DIRECTION_DOWN));

  depth = depth.lower();

  EXPECT_TRUE(depth.has_more_levels(Direction::DIRECTION_DOWN));

  depth = depth.lower();

  EXPECT_FALSE(depth.has_more_levels(Direction::DIRECTION_DOWN));
}

TEST(SW_World_Depth, has_more_levels_asc)
{
  Depth depth(0, -2, 0, -1, true);

  EXPECT_TRUE(depth.has_more_levels(Direction::DIRECTION_UP));

  depth = depth.higher();

  EXPECT_TRUE(depth.has_more_levels(Direction::DIRECTION_UP));

  depth = depth.higher();

  EXPECT_FALSE(depth.has_more_levels(Direction::DIRECTION_UP));
}

TEST(SW_World_Depth, to_str)
{
  Depth depth(0, -5, 5, 1, true);

  EXPECT_EQ("[0']", depth.str(true));
  EXPECT_EQ("", depth.str());
  EXPECT_EQ("", depth.str(false));

  depth.set_current(3);
  string exp_val = "[-150']";

  EXPECT_EQ(exp_val, depth.str(true));
  EXPECT_EQ(exp_val, depth.str(false));
  EXPECT_EQ(exp_val, depth.str());
}