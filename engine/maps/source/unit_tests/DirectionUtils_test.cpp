#include "gtest/gtest.h"

TEST(SL_Engine_Maps_DirectionUtils, is_cardinal)
{
  EXPECT_TRUE(DirectionUtils::is_cardinal(DIRECTION_NORTH));
  EXPECT_TRUE(DirectionUtils::is_cardinal(DIRECTION_SOUTH));
  EXPECT_TRUE(DirectionUtils::is_cardinal(DIRECTION_EAST));
  EXPECT_TRUE(DirectionUtils::is_cardinal(DIRECTION_WEST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(DIRECTION_NORTH_EAST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(DIRECTION_NORTH_WEST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(DIRECTION_UP));
}

TEST(SL_Engine_Maps_DirectionUtils, is_ordinal)
{
  EXPECT_TRUE(DirectionUtils::is_ordinal(DIRECTION_NORTH_WEST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(DIRECTION_NORTH_EAST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(DIRECTION_SOUTH_WEST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(DIRECTION_SOUTH_EAST));
  EXPECT_FALSE(DirectionUtils::is_ordinal(DIRECTION_NORTH));
  EXPECT_FALSE(DirectionUtils::is_ordinal(DIRECTION_DOWN));
}

TEST(SL_Engine_Maps_DirectionUtils, get_opposite_direction)
{
  EXPECT_EQ(DIRECTION_SOUTH_EAST, DirectionUtils::get_opposite_direction(DIRECTION_NORTH_WEST));
  EXPECT_EQ(DIRECTION_SOUTH, DirectionUtils::get_opposite_direction(DIRECTION_NORTH));
  EXPECT_EQ(DIRECTION_SOUTH_WEST, DirectionUtils::get_opposite_direction(DIRECTION_NORTH_EAST));
  EXPECT_EQ(DIRECTION_EAST, DirectionUtils::get_opposite_direction(DIRECTION_WEST));
  EXPECT_EQ(DIRECTION_NULL, DirectionUtils::get_opposite_direction(DIRECTION_NULL));
  EXPECT_EQ(DIRECTION_WEST, DirectionUtils::get_opposite_direction(DIRECTION_EAST));
  EXPECT_EQ(DIRECTION_NORTH_EAST, DirectionUtils::get_opposite_direction(DIRECTION_SOUTH_WEST));
  EXPECT_EQ(DIRECTION_NORTH, DirectionUtils::get_opposite_direction(DIRECTION_SOUTH));
  EXPECT_EQ(DIRECTION_NORTH_WEST, DirectionUtils::get_opposite_direction(DIRECTION_SOUTH_EAST));
  EXPECT_EQ(DIRECTION_UP, DirectionUtils::get_opposite_direction(DIRECTION_DOWN));
  EXPECT_EQ(DIRECTION_DOWN, DirectionUtils::get_opposite_direction(DIRECTION_UP));
}
