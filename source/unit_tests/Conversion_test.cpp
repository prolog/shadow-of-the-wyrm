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

  string x_s = string(1, x);
  string three_s = string(1, three);

  EXPECT_EQ("x", x_s);
  EXPECT_EQ("3", three_s);
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

  EXPECT_EQ(static_cast<uint>(3), t1_v.size());

  t1_v = String::tokenize(test1, "\n", true);

  EXPECT_EQ(static_cast<uint>(5), t1_v.size());
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

TEST(SW_Engine_ConversionRoutines, csv_to_string_set)
{
  string csv_no_repeat = "1,2,3";
  string csv_repeat = "1,1,2,2,3,3,3,4,5";

  set<string> csv_set_no_repeat = String::create_string_set_from_csv_string(csv_no_repeat);
  set<string> csv_set_repeat = String::create_string_set_from_csv_string(csv_repeat);

  vector<string> exp_v_no_repeat = { "1", "2", "3" };
  vector<string> exp_v_repeat = { "1", "2", "3", "4", "5" };

  EXPECT_EQ(static_cast<uint>(3), csv_set_no_repeat.size());
  EXPECT_EQ(static_cast<uint>(5), csv_set_repeat.size());

  for (const auto& ei : exp_v_no_repeat)
  {
    EXPECT_TRUE(csv_set_no_repeat.find(ei) != csv_set_no_repeat.end());
  }

  for (const auto& ei : exp_v_repeat)
  {
    EXPECT_TRUE(csv_set_repeat.find(ei) != csv_set_repeat.end());
  }
}

TEST(SW_Engine_ConversionRoutines, csv_to_int_vector)
{
  vector<int> expected = { 1,5,3,4 };
  string csv = "1,5,fish,3,4";
  vector<int> i_vec = String::create_int_vector_from_csv_string(csv);

  EXPECT_EQ(static_cast<uint>(4), i_vec.size());
  EXPECT_EQ(expected, i_vec);
}

TEST(SW_Engine_ConversionRoutines, csv_to_colour_vector)
{
  vector<Colour> expected = { Colour::COLOUR_RED, Colour::COLOUR_YELLOW, Colour::COLOUR_BOLD_RED, Colour::COLOUR_BLUE };
  string csv = "1,3,fish,9,4";
  vector<Colour> c_vec = String::create_colour_vector_from_csv_string(csv);

  EXPECT_EQ(static_cast<uint>(4), c_vec.size());
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

TEST(SW_Engine_ConversionRoutines, map_to_csv)
{
  map<string, string> props;
  props["a"] = "b";
  props["test"] = "4324";
  props["some_prop"] = "val";

  EXPECT_EQ("a=b,some_prop=val,test=4324", String::create_csv_from_string_map(props));
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

TEST(SW_Engine_ConversionRoutines, coord_to_string)
{
  Coordinate c(3,4);

  EXPECT_EQ("3,4", String::create_string_from_coordinate(c));

  c = {-12, 6};

  EXPECT_EQ("-12,6", String::create_string_from_coordinate(c));
}

TEST(SW_Engine_ConversionRoutines, string_to_coord)
{
  string coord_s = "3,4";

  Coordinate c(3,4);

  EXPECT_EQ(c, String::create_coordinate_from_string(coord_s));

  coord_s = "3 , 4";

  EXPECT_EQ(c, String::create_coordinate_from_string(coord_s));

  EXPECT_TRUE(CoordUtils::is_end(String::create_coordinate_from_string("")));
  EXPECT_TRUE(CoordUtils::is_end(String::create_coordinate_from_string("3")));
  EXPECT_TRUE(CoordUtils::is_end(String::create_coordinate_from_string("4,")));

  EXPECT_FALSE(CoordUtils::is_end(String::create_coordinate_from_string("4,5")));
}

TEST(SW_Engine_ConversionRoutines, dimensions_string_to_pair)
{
  string bad = "hithere";
  pair<int, int> wh = String::create_width_height(bad);

  EXPECT_EQ(0, wh.first);
  EXPECT_EQ(0, wh.second);

  string good = "1500x600";
  wh = String::create_width_height(good);

  EXPECT_EQ(1500, wh.first);
  EXPECT_EQ(600, wh.second);
}

TEST(SW_Engine_ConversionRoutines, harmonize_dirname)
{
  string fs_sep(1, FS_PATH_SEPARATOR);

  EXPECT_EQ("", File::harmonize_dirname(""));
  EXPECT_EQ("a" + fs_sep, File::harmonize_dirname("a"));
  EXPECT_EQ("/var" + fs_sep, File::harmonize_dirname("/var"));
  EXPECT_EQ("/var/root" + fs_sep, File::harmonize_dirname("/var/root"));
  EXPECT_EQ("/var/root" + fs_sep, File::harmonize_dirname("/var/root" + fs_sep));
  EXPECT_EQ("C:\\temp" + fs_sep, File::harmonize_dirname("C:\\temp"));
  EXPECT_EQ("C:\\temp" + fs_sep, File::harmonize_dirname("C:\\temp" + fs_sep));
}

TEST(SW_Engine_ConversionRoutines, clean_and_trim)
{

}

TEST(SW_Engine_ConversionRoutines, split)
{
  string str_ns = "abcdsa 123 1 jsklSJL 2 321 123 A";
  string str_sp = "abc %p test";
  string delim = "%p";

  vector<string> strs = String::split(str_ns, delim);

  EXPECT_EQ(static_cast<size_t>(1), strs.size());
  EXPECT_EQ(str_ns, strs.at(0));

  strs = String::split(str_sp, delim);

  EXPECT_EQ(static_cast<size_t>(2), strs.size());
  EXPECT_EQ("abc ", strs.at(0));
  EXPECT_EQ(" test", strs.at(1));
}
