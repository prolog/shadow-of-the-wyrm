#include "gtest/gtest.h"

TEST(SL_Engine_ConversionRoutines, string_to_bool)
{
  string test_1 = "1";
  string test_2 = "true";
  string test_3 = "0";
  string test_4 = "false";

  EXPECT_TRUE(String::to_bool(test_1));
  EXPECT_TRUE(String::to_bool(test_2));
  EXPECT_FALSE(String::to_bool(test_3));
  EXPECT_FALSE(String::to_bool(test_4));
}

TEST(SL_Engine_ConversionRoutines, string_to_int)
{
  string test_1 = "1";
  string test_2 = "0";
  string test_3 = "-1";
  string test_4 = "9999";
  string test_5 = "-9999";

  EXPECT_EQ(1, String::to_int(test_1));
  EXPECT_EQ(0, String::to_int(test_2));
  EXPECT_EQ(-1, String::to_int(test_3));
  EXPECT_EQ(9999, String::to_int(test_4));
  EXPECT_EQ(-9999, String::to_int(test_5));
}

TEST(SL_Engine_ConversionRoutines, string_to_float)
{
  string test_1 = "0.00";
  string test_2 = "-3.6";
  string test_3 = "54.95";

  EXPECT_FLOAT_EQ(0.0, String::to_float(test_1));
  EXPECT_FLOAT_EQ(-3.6, String::to_float(test_2));
  EXPECT_FLOAT_EQ(54.95, String::to_float(test_3));
}

TEST(SL_Engine_ConversionRoutines, char_to_string)
{
  char x = 'x';
  char three = '3';

  EXPECT_EQ("x", Char::to_string(x));
  EXPECT_EQ("3", Char::to_string(three));
}

TEST(SL_Engine_ConversionRoutines, direction_to_string)
{
  EXPECT_EQ(CommandKeys::MOVE_SOUTHEAST, DirectionEnum::to_string(DIRECTION_SOUTH_EAST));
  EXPECT_EQ(CommandKeys::MOVE_SOUTH, DirectionEnum::to_string(DIRECTION_SOUTH));
  EXPECT_EQ(CommandKeys::MOVE_SOUTHWEST, DirectionEnum::to_string(DIRECTION_SOUTH_WEST));
  EXPECT_EQ(CommandKeys::MOVE_EAST, DirectionEnum::to_string(DIRECTION_EAST));
  EXPECT_EQ(CommandKeys::MOVE_WEST, DirectionEnum::to_string(DIRECTION_WEST));
  EXPECT_EQ(CommandKeys::MOVE_NORTHWEST, DirectionEnum::to_string(DIRECTION_NORTH_WEST));
  EXPECT_EQ(CommandKeys::MOVE_NORTH, DirectionEnum::to_string(DIRECTION_NORTH));
  EXPECT_EQ(CommandKeys::MOVE_NORTHEAST, DirectionEnum::to_string(DIRECTION_NORTH_EAST));
}

TEST(SL_Engine_ConversionRoutines, int_to_string)
{
  int test_1 = 1;
  int test_2 = 0;
  int test_3 = -1;
  int test_4 = 9999;
  int test_5 = -9999;

  string converted_test_1 = "1";
  string converted_test_2 = "0";
  string converted_test_3 = "-1";
  string converted_test_4 = "9999";
  string converted_test_5 = "-9999";

  EXPECT_EQ(converted_test_1, Integer::to_string(test_1));
  EXPECT_EQ(converted_test_2, Integer::to_string(test_2));
  EXPECT_EQ(converted_test_3, Integer::to_string(test_3));
  EXPECT_EQ(converted_test_4, Integer::to_string(test_4));
  EXPECT_EQ(converted_test_5, Integer::to_string(test_5));
}
