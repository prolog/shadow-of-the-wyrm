#include "gtest/gtest.h"

TEST(SL_Engine_MessageBuffer, insertion)
{
  MessageBuffer mb(3);

  mb.add_message("a");
  mb.add_message("b");
  mb.add_message("c");

  EXPECT_EQ("a", mb.get_message(2));

  mb.add_message("d");
  mb.add_message("e");

  // "a" and "b" should have been removed:
  EXPECT_EQ("e", mb.get_message(0));
  EXPECT_EQ("d", mb.get_message(1));
  EXPECT_EQ("c", mb.get_message(2));

  EXPECT_EQ(3, mb.capacity());
  EXPECT_EQ(3, mb.size());
}

TEST(SL_Engine_MessageBuffer, serialization_id)
{
  MessageBuffer mb;
  EXPECT_EQ(ClassIdentifier::CLASS_ID_MESSAGE_BUFFER, mb.get_class_identifier());
}

TEST(SL_Engine_MessageBuffer, saveload)
{
  MessageBuffer mb;
  MessageBuffer mb2;

  ostringstream ss;

  mb.serialize(ss);

  istringstream iss(ss.str());

  mb2.deserialize(iss);

  EXPECT_TRUE(mb == mb2);
}

