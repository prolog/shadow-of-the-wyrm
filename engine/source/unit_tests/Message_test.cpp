#include "gtest/gtest.h"

TEST(SL_Engine_Message, MessageImportanceValues)
{
  EXPECT_EQ(MessageImportance_UNDEFINED, -1);
  EXPECT_EQ(MessageImportance_Normal, 0);
  EXPECT_EQ(MessageImportance_High, 1);
  EXPECT_EQ(MessageImportance_Critical, 2);
}

TEST(SL_Engine_Message, Content)
{
  Message msg("test", Colour::COLOUR_WHITE, MessageImportance::MessageImportance_UNDEFINED);

  EXPECT_EQ("test", msg.get_content());

  msg.set_content("test2");
  
  EXPECT_EQ("test2", msg.get_content());
}

TEST(SL_Engine_Message, Colour)
{
  Message msg("test", Colour::COLOUR_RED, MessageImportance::MessageImportance_UNDEFINED);

  EXPECT_EQ(Colour::COLOUR_RED, msg.get_colour());
}

TEST(SL_Engine_Message, Importance)
{
  Message msg("test", Colour::COLOUR_WHITE, MessageImportance::MessageImportance_UNDEFINED);

  EXPECT_EQ(MessageImportance::MessageImportance_UNDEFINED, msg.get_importance());

  msg.set_importance(MessageImportance::MessageImportance_Normal);

  EXPECT_EQ(MessageImportance::MessageImportance_Normal, msg.get_importance());

  msg.set_importance(MessageImportance::MessageImportance_High);

  EXPECT_EQ(MessageImportance::MessageImportance_High, msg.get_importance());

  msg.set_importance(MessageImportance::MessageImportance_Critical);

  EXPECT_EQ(MessageImportance::MessageImportance_Critical, msg.get_importance());
}

TEST(SL_Engine_Message, Id)
{
  boost::uuids::uuid id = boost::uuids::random_generator()();
  Message msg("test", COLOUR_WHITE, MessageImportance_UNDEFINED);

  msg.set_id(id);
  EXPECT_EQ(id, msg.get_id());

  
}
