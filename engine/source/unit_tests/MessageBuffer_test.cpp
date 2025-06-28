#include "gtest/gtest.h"

TEST(SW_Engine_MessageBuffer, insertion)
{
  MessageBuffer mb(3);
  mb.add_message("a", Colour::COLOUR_RED);
  mb.add_message("b", Colour::COLOUR_GREEN);
  mb.add_message("c", Colour::COLOUR_BLUE);

  pair<string, Colour> exp_a = make_pair("a", Colour::COLOUR_RED);
  EXPECT_EQ(exp_a, mb.get_message(2));

  mb.add_message("d", Colour::COLOUR_YELLOW);
  mb.add_message("e", Colour::COLOUR_CYAN);

  pair<string, Colour> exp_c = make_pair("c", Colour::COLOUR_BLUE);
  pair<string, Colour> exp_d = make_pair("d", Colour::COLOUR_YELLOW);
  pair<string, Colour> exp_e = make_pair("e", Colour::COLOUR_CYAN);

  // "a" and "b" should have been removed:
  EXPECT_EQ(exp_e, mb.get_message(0));
  EXPECT_EQ(exp_d, mb.get_message(1));
  EXPECT_EQ(exp_c, mb.get_message(2));

  EXPECT_EQ(static_cast<size_t>(3), mb.capacity());
  EXPECT_EQ(static_cast<size_t>(3), mb.size());
}

TEST(SW_Engine_MessageBuffer, serialization_id)
{
  MessageBuffer mb;
  EXPECT_EQ(ClassIdentifier::CLASS_ID_MESSAGE_BUFFER, mb.get_class_identifier());
}

TEST(SW_Engine_MessageBuffer, saveload)
{
  MessageBuffer mb;
  MessageBuffer mb2;

  ostringstream ss;

  mb.add_message("test", Colour::COLOUR_WHITE);
  mb.serialize(ss);

  istringstream iss(ss.str());

  mb2.deserialize(iss);

  EXPECT_TRUE(mb == mb2);
}

