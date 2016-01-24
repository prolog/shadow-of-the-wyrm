#include "gtest/gtest.h"

TEST(SW_Engine_Serialization_Serialize, string_map)
{
  map<string, string> orig;
  orig["s1"] = "foo";
  orig["s2"] = "fdsa";
  orig["fdsafdsa"] = "asdf";
  orig["jcd"] = "clf";

  ostringstream oss;

  Serialize::write_string_map(oss, orig);

  istringstream iss(oss.str());

  map<string, string> after;

  Serialize::read_string_map(iss, after);

  EXPECT_TRUE(orig == after);
}

TEST(SW_Engine_Serialization_Serialize, string_vector)
{
  vector<string> original;

  original.push_back("foo");
  original.push_back("jules");
  original.push_back("blah");

  ostringstream oss;

  Serialize::write_string_vector(oss, original);

  istringstream iss(oss.str());

  vector<string> deserialized_vector;

  Serialize::read_string_vector(iss, deserialized_vector);

  EXPECT_TRUE(original == deserialized_vector);
}

