#include "gtest/gtest.h"

TEST(SW_Engine_Messages, Add)
{
  Messages messages;
  Message  msg("test", Colour::COLOUR_WHITE, MessageImportance::MessageImportance_UNDEFINED);

  messages.add(msg);
  messages.add(msg);

  std::vector<Message> internal_messages = messages.get_messages();
  int size = internal_messages.size();
  EXPECT_EQ(2, size);
}

TEST(SW_Engine_Messages, Clear)
{
  Messages messages;
  Message  msg("test", Colour::COLOUR_WHITE, MessageImportance::MessageImportance_UNDEFINED);

  messages.add(msg);
  messages.add(msg);

  std::vector<Message> internal_messages = messages.get_messages();
  int size = internal_messages.size();

  EXPECT_EQ(2, size);

  messages.clear();

  internal_messages = messages.get_messages();
  size = internal_messages.size();

  EXPECT_EQ(0, size);
}
