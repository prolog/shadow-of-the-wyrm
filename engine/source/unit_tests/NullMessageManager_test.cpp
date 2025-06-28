#include "gtest/gtest.h"
#include "MessageManagerFactory.hpp"

TEST(SW_Engine_NullMessageManager, add_does_nothing)
{
  IMessageManager& nmm = MMF::instance(MessageTransmit::NONE, nullptr, false);
  nmm.add_new_message("fdsa");
  nmm.add_new_message("blah");

  Messages m = nmm.get_unread_messages();
  EXPECT_TRUE(m.empty());
}

TEST(SW_Engine_NullMessageManager, send_returns_false)
{
  IMessageManager& nmm = MMF::instance(MessageTransmit::NONE, nullptr, false);

  EXPECT_FALSE(nmm.send());
}

