#include "gtest/gtest.h"

TEST(SW_Engine_ConversionRoutines, string_to_bool)
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

TEST(SW_Engine_ConversionRoutines, string_to_int)
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

TEST(SW_Engine_ConversionRoutines, string_to_float)
{
  string test_1 = "0.00";
  string test_2 = "-3.6";
  string test_3 = "54.95";

  EXPECT_FLOAT_EQ(0.0f, String::to_float(test_1));
  EXPECT_FLOAT_EQ(-3.6f, String::to_float(test_2));
  EXPECT_FLOAT_EQ(54.95f, String::to_float(test_3));
}

TEST(SW_Engine_ConversionRoutines, string_to_colour)
{
  EXPECT_EQ(Colour::COLOUR_WHITE, String::to_colour("", Colour::COLOUR_WHITE));
  EXPECT_EQ(Colour::COLOUR_BLUE, String::to_colour("", Colour::COLOUR_BLUE));

  EXPECT_EQ(Colour::COLOUR_BOLD_RED, String::to_colour("9", Colour::COLOUR_WHITE));
  EXPECT_EQ(Colour::COLOUR_GREEN, String::to_colour("2", Colour::COLOUR_WHITE));
}

TEST(SW_Engine_ConversionRoutines, char_to_string)
{
  char x = 'x';
  char three = '3';

  EXPECT_EQ("x", Char::to_string(x));
  EXPECT_EQ("3", Char::to_string(three));
}

TEST(SW_Engine_ConversionRoutines, float_to_string)
{
  EXPECT_EQ("1.23", Float::to_string(1.234567f, 3));
  EXPECT_EQ("3.14159", Float::to_string(3.1415926535f, 6));
}

TEST(SW_Engine_ConversionRoutines, tokenize)
{
  string test1 = "fdsa\nasdf\nbbb";
  vector<string> t1_v = String::tokenize(test1, "\n", false);

  EXPECT_EQ(3, t1_v.size());

  t1_v = String::tokenize(test1, "\n", true);

  EXPECT_EQ(5, t1_v.size());
}

TEST(SW_Engine_ConversionRoutines, csv_to_vector)
{
  string csv = "first,second,third";
  vector<string> str_vec = String::create_string_vector_from_csv_string(csv);

  EXPECT_EQ("third", str_vec.back());

  str_vec.pop_back();

  EXPECT_EQ("second", str_vec.back());

  str_vec.pop_back();

  EXPECT_EQ("first", str_vec.back());
}

TEST(SW_Engine_ConversionRoutines, csv_to_int_vector)
{
  vector<int> expected = { 1,5,3,4 };
  string csv = "1,5,fish,3,4";
  vector<int> i_vec = String::create_int_vector_from_csv_string(csv);

  EXPECT_EQ(4, i_vec.size());
  EXPECT_EQ(expected, i_vec);
}

TEST(SW_Engine_ConversionRoutines, csv_to_colour_vector)
{
  vector<Colour> expected = { Colour::COLOUR_RED, Colour::COLOUR_YELLOW, Colour::COLOUR_BOLD_RED, Colour::COLOUR_BLUE };
  string csv = "1,3,fish,9,4";
  vector<Colour> c_vec = String::create_colour_vector_from_csv_string(csv);

  EXPECT_EQ(4, c_vec.size());
  EXPECT_EQ(expected, c_vec);
}

TEST(SW_Engine_ConversionRoutines, vector_to_csv)
{
  vector<string> foo;

  EXPECT_EQ("", String::create_csv_from_string_vector(foo));

  foo.push_back("foo");
  foo.push_back("bar");
  foo.push_back("baz");
  foo.push_back("quux");

  EXPECT_EQ("foo,bar,baz,quux", String::create_csv_from_string_vector(foo));
}

TEST(SW_Engine_ConversionRoutines, create_properties_from_string)
{
  map<string, string> props;

  props = String::create_properties_from_string("a=b,c=d");

  auto p_it = props.find("a");

  EXPECT_TRUE(p_it != props.end());
  EXPECT_EQ("b", p_it->second);

  p_it = props.find("c");

  EXPECT_TRUE(p_it != props.end());
  EXPECT_EQ("d", p_it->second);

  p_it = props.find("fdsa");

  EXPECT_FALSE(p_it != props.end());
}