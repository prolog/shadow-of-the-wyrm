#include "gtest/gtest.h"

TEST(SW_World_ScriptDetails, serialization_id)
{
  ScriptDetails sd;
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SCRIPT_DETAILS, sd.get_class_identifier());
}

TEST(SW_World_ScriptDetails, saveload)
{
  ScriptDetails sd("abc", 88);

  ostringstream oss;
  sd.serialize(oss);

  ScriptDetails sd2;

  istringstream iss(oss.str());

  sd2.deserialize(iss);

  EXPECT_TRUE(sd == sd2);
}

