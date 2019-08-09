#include "gtest/gtest.h"

TEST(SW_Engine_Screens_Option, get_id_char_uppercase_tests)
{
  Option o;
  o.set_id(0);

  EXPECT_FALSE(o.get_uppercase());
  EXPECT_EQ('a', o.get_id_char());

  o.set_uppercase(true);

  EXPECT_TRUE(o.get_uppercase());

  EXPECT_EQ('A', o.get_id_char());

  o.set_id(1);
  o.set_uppercase(false);

  EXPECT_FALSE(o.get_uppercase());
  EXPECT_EQ('b', o.get_id_char());

  o.set_uppercase(true);

  EXPECT_TRUE(o.get_uppercase());

  EXPECT_EQ('B', o.get_id_char());
}

