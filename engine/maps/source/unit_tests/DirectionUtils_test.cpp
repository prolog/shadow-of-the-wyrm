#include "gtest/gtest.h"

TEST(SL_Engine_Maps_DirectionUtils, is_cardinal)
{
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_NORTH));
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_SOUTH));
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_EAST));
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_WEST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(Direction::DIRECTION_NORTH_EAST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(Direction::DIRECTION_NORTH_WEST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(Direction::DIRECTION_UP));
}

TEST(SL_Engine_Maps_DirectionUtils, is_ordinal)
{
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_NORTH_WEST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_NORTH_EAST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_SOUTH_WEST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_SOUTH_EAST));
  EXPECT_FALSE(DirectionUtils::is_ordinal(Direction::DIRECTION_NORTH));
  EXPECT_FALSE(DirectionUtils::is_ordinal(Direction::DIRECTION_DOWN));
}

TEST(SL_Engine_Maps_DirectionUtils, get_opposite_direction)
{
  EXPECT_EQ(Direction::DIRECTION_SOUTH_EAST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NORTH_WEST));
  EXPECT_EQ(Direction::DIRECTION_SOUTH, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NORTH));
  EXPECT_EQ(Direction::DIRECTION_SOUTH_WEST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NORTH_EAST));
  EXPECT_EQ(Direction::DIRECTION_EAST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_WEST));
  EXPECT_EQ(Direction::DIRECTION_NULL, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NULL));
  EXPECT_EQ(Direction::DIRECTION_WEST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_EAST));
  EXPECT_EQ(Direction::DIRECTION_NORTH_EAST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_SOUTH_WEST));
  EXPECT_EQ(Direction::DIRECTION_NORTH, DirectionUtils::get_opposite_direction(Direction::DIRECTION_SOUTH));
  EXPECT_EQ(Direction::DIRECTION_NORTH_WEST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_SOUTH_EAST));
  EXPECT_EQ(Direction::DIRECTION_UP, DirectionUtils::get_opposite_direction(Direction::DIRECTION_DOWN));
  EXPECT_EQ(Direction::DIRECTION_DOWN, DirectionUtils::get_opposite_direction(Direction::DIRECTION_UP));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_SOUTH, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_NORTH));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_NORTH, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_SOUTH));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_EAST, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_WEST));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_WEST, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_EAST));
}
