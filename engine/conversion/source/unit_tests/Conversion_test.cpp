#include "gtest/gtest.h"
#include "Amulet.hpp"

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

TEST(SW_Engine_ConversionRoutines, direction_to_string)
{
  EXPECT_EQ(CommandKeys::MOVE_SOUTHEAST, DirectionEnum::to_string(Direction::DIRECTION_SOUTH_EAST));
  EXPECT_EQ(CommandKeys::MOVE_SOUTH, DirectionEnum::to_string(Direction::DIRECTION_SOUTH));
  EXPECT_EQ(CommandKeys::MOVE_SOUTHWEST, DirectionEnum::to_string(Direction::DIRECTION_SOUTH_WEST));
  EXPECT_EQ(CommandKeys::MOVE_EAST, DirectionEnum::to_string(Direction::DIRECTION_EAST));
  EXPECT_EQ(CommandKeys::MOVE_WEST, DirectionEnum::to_string(Direction::DIRECTION_WEST));
  EXPECT_EQ(CommandKeys::MOVE_NORTHWEST, DirectionEnum::to_string(Direction::DIRECTION_NORTH_WEST));
  EXPECT_EQ(CommandKeys::MOVE_NORTH, DirectionEnum::to_string(Direction::DIRECTION_NORTH));
  EXPECT_EQ(CommandKeys::MOVE_NORTHEAST, DirectionEnum::to_string(Direction::DIRECTION_NORTH_EAST));
}

TEST(SW_Engine_ConversionRoutines, raw_hunger_to_hunger_level)
{
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_STUFFED, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_FULL, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_FULL));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_NORMAL, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_HUNGRY, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_HUNGRY));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_STARVING, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_STARVING));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_DYING, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_DYING));
}

TEST(SW_Engine_ConversionRoutines, grams_per_standard_drink)
{
  EXPECT_FLOAT_EQ(13.6f, AlcoholConverter::standard_drinks_to_grams(1.0f));
  EXPECT_FLOAT_EQ(27.2f, AlcoholConverter::standard_drinks_to_grams(2.0f));
  EXPECT_FLOAT_EQ(34.0f, AlcoholConverter::standard_drinks_to_grams(2.5f));
}

TEST(SW_Engine_ConversionRoutines, weight_to_burden_level)
{
  CreaturePtr c = std::make_shared<Creature>();
  Statistic strength(10);
  c->set_strength(10);
  c->set_size(CreatureSize::CREATURE_SIZE_MEDIUM);

  ItemPtr amulet = std::make_shared<Amulet>();
  Weight amulet_weight;
  amulet_weight.set_weight(16); // 1 lb
  amulet->set_weight(amulet_weight);

  c->get_inventory()->add_front(amulet);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_UNBURDENED, BurdenLevelConverter::to_burden_level(c));

  amulet->set_quantity(125);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_BURDENED, BurdenLevelConverter::to_burden_level(c));

  amulet->set_quantity(175);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_STRAINED, BurdenLevelConverter::to_burden_level(c));

  amulet->set_quantity(325);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_OVERBURDENED, BurdenLevelConverter::to_burden_level(c));
}