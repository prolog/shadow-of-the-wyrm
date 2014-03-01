#include "gtest/gtest.h"

TEST(SL_World_Conducts, serialization_id)
{
  Conducts c;
  EXPECT_EQ(CLASS_ID_CONDUCTS, c.get_class_identifier());
}

TEST(SL_World_Conducts, saveload)
{
  Conducts c;
  
  c.break_conduct(CONDUCT_TYPE_FOODLESS);

  Conducts c2;

  ostringstream ss;
  c.serialize(ss);

  istringstream iss(ss.str());

  c2.deserialize(iss);

  EXPECT_TRUE(c == c2);
}

