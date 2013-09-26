#include "gtest/gtest.h"

TEST(SL_Engine_Serialization_Serialize, string_vector)
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

