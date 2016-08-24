#include "gtest/gtest.h"

TEST(SW_World_Marks, serialization_id)
{
  Marks m;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MARKS, m.get_class_identifier());
}

TEST(SW_World_Marks, saveload)
{
  Marks m(55);

  ostringstream ss;
  m.serialize(ss);

  istringstream iss(ss.str());

  Marks m2;

  m2.deserialize(iss);

  EXPECT_TRUE(m == m2);
}

