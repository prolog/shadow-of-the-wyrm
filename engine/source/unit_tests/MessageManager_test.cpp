#include "gtest/gtest.h"
#include "MessageManagerFactory.hpp"

TEST(SW_Engine_MessageManager, mark_as_read)
{
  IMessageManager& mm = MM::instance();
  mm.add_new_message("fdsa");

  Messages m = mm.get_unread_messages_and_mark_as_read();
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(1, m.get_messages().size());

  mm.clear_if_necessary();

  m = mm.get_unread_messages();
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(0, m.get_messages().size());
}

TEST(SW_Engine_MessageManager, add_new_message)
{
  IMessageManager& mm = MM::instance();
  mm.add_new_message("fdsa");
  mm.add_new_message("blah");

  Messages m = mm.get_unread_messages();
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(2, m.get_messages().size());
}


TEST(SW_Engine_MessageManager, send_returns_true)
{
  IMessageManager& mm = MM::instance();
  EXPECT_TRUE(mm.send());
}

