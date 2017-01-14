#include "gtest/gtest.h"

TEST(SW_World_Tool, additional_item_attributes)
{
  ToolPtr tool1 = std::make_shared<Tool>();
  ToolPtr tool2 = std::make_shared<Tool>();

  EXPECT_TRUE(tool1->additional_item_attributes_match(tool2));
  
  tool2->set_lock_id("door1");

  EXPECT_FALSE(tool1->additional_item_attributes_match(tool2));

  tool1->set_lock_id("door1");
}

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
