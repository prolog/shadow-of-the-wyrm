#include "gtest/gtest.h"

TEST(SW_World_Tool, serialization_id)
{
  Tool tool;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TOOL, tool.get_class_identifier());
}

TEST(SW_World_Tool, saveload)
{
  Tool tool, tool2;

  tool.set_quantity(5000);

  ostringstream ss;

  tool.serialize(ss);

  istringstream iss(ss.str());

  tool2.deserialize(iss);

  EXPECT_TRUE(tool == tool2);
}
