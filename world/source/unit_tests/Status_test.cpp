#include "gtest/gtest.h"

TEST(SW_World_Status, serialization_id)
{
  Status s;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STATUS, s.get_class_identifier());
}

TEST(SW_World_Status, saveload)
{
  Status s("abc", true, 34, "123");
  ostringstream ss;

  s.serialize(ss);

  istringstream iss(ss.str());

  Status s2;

  s2.deserialize(iss);

  EXPECT_TRUE(s == s2);
}

